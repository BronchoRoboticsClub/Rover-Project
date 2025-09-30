import rclpy
from rclpy.node import Node
from rover_interfaces.msg import Control
import serial



class MotorControl(Node):
    def __init__(self):
        super().__init__("motor_control")
        self.subscriber_ = self.create_subscription(Control, "controller", self.handle_received_inputs, 10)
        self.get_logger().info("Motor Control node has started")

    def handle_received_inputs(self, msg: Control):
        self.get_logger().info(f"Motor Speed: {msg.speed}")
        # Serial write motor speed to arduino



def main(args=None):
    rclpy.init(args=args)
    node = MotorControl()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()