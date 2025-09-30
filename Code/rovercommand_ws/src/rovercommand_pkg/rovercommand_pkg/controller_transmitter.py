import rclpy
from rclpy.node import Node
from rover_interfaces.msg import Control
from evdev import InputDevice, categorize, ecodes
import math




MAX_ANGLE_DEGREES = 80
MAX_ANGLE_RADIANS = MAX_ANGLE_DEGREES * (math.pi / 180)
STICK_DEADZONE = 0.01

try:
    gamepad = InputDevice('/dev/input/event13')
except FileNotFoundError:
    print("Can't connect to controller or controller not found")
    exit()

def get_axis_value(i):
    return (gamepad.absinfo(i).value - 128) / 128


# Will want to use this in the future, but for now let's just do steering angle and speed
# def axes_to_vector(LX, RY):
#     # Using right stick for magnitude (speed)
#     # Left stick for angle
#     # In this case RX and LY are not used

#     # Map RX to steering angle between -MAX_ANGLE and +MAX ANGLE in radians
#     # All axis values are from -1 to 1, so to map we multiply by MAX_ANGLE

#     LX = LX * MAX_ANGLE

#     x = RY * math.cos(LX)
#     y = RY * math.sin(LX)
#     return [x, y]



# Returns a vector [Speed, Steering Angle]
def axes_to_control(LX, RY):
    # Steering angle mapped to max angle +/-
    # Negative angle is LEFT, positive angle is RIGHT
    return [RY, LX]



class ControllerTransmitter(Node):
    def __init__(self):
        super().__init__("controller_transmitter")
        self.publisher_ = self.create_publisher(Control, "controller", 0)

        self.get_logger().info("Controller Transmitter Node Started")
        self.get_logger().info(f"Connected to {str(gamepad)}")


    def handle_input(self):
    
        for event in gamepad.read_loop():
            if event.type == ecodes.EV_ABS:

                [LX, LY, RX, RY] = map(get_axis_value, [0,1,3,4])

                if (LX > STICK_DEADZONE or LX < -STICK_DEADZONE or LY > STICK_DEADZONE or LY < -STICK_DEADZONE or RX > STICK_DEADZONE or RX < -STICK_DEADZONE or RY > STICK_DEADZONE or RY < -STICK_DEADZONE):
                    RY = -1 * RY # Change sign so UP is positive and DOWN is negative
                    
                    vector = axes_to_control(LX, RY)
                    
                    msg = Control()
                    if (abs(vector[0]*100) <=5):
                        msg.speed = int(0).to_bytes(1, 'little')
                    else:
                        msg.speed = int(abs(vector[0]*100)).to_bytes(1, 'little')
                    self.get_logger().info(f"{msg.speed}")
                    msg.steering_angle = int((LX+1)*90).to_bytes(1, 'little')
                    self.publisher_.publish(msg)

                    self.get_logger().info(f"{msg.steering_angle}")


def main(args=None):
    rclpy.init(args=args)
    node = ControllerTransmitter()
    node.handle_input()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
