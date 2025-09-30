
import rclpy
from rclpy.node import Node
from rover_interfaces.msg import Control
import serial
import struct
import time
import math

ser = serial.Serial('/dev/ttyACM0', 9600)

class SteeringControl(Node):
    def __init__(self):
        super().__init__("steering_control")
        self.subscriber_ = self.create_subscription(Control, "controller", self.handle_received_inputs, 10)
        self.get_logger().info("Steering Control node has started")

    def handle_received_inputs(self, msg: Control):
        target_angle = int.from_bytes(msg.steering_angle, 'little')
        target_angle = float(target_angle-90)
        speed = int.from_bytes(msg.speed, 'little')
        self.get_logger().info(f"Steering Angle: {target_angle}")
        if (target_angle < -50.0 or target_angle > 50.0):
            return
        FR_angle = math.degrees((math.atan((2*0.284*math.sin(math.radians(target_angle)))/(2*0.284*math.cos(math.radians(target_angle))-0.464*math.sin(math.radians(target_angle))))))
        FL_angle = math.degrees((math.atan((2*0.284*math.sin(math.radians(target_angle)))/(2*0.284*math.cos(math.radians(target_angle))+0.464*math.sin(math.radians(target_angle))))))
        RR_angle = math.degrees((math.atan((2*0.343*math.sin(math.radians(-1*target_angle)))/(2*0.343*math.cos(math.radians(-1*target_angle))+0.464*math.sin(math.radians(-1*target_angle))))))
        RL_angle = math.degrees((math.atan((2*0.343*math.sin(math.radians(-1*target_angle)))/(2*0.343*math.cos(math.radians(-1*target_angle))-0.464*math.sin(math.radians(-1*target_angle))))))
        FR_angle = int(FR_angle)+90
        FL_angle = int(FL_angle)+90
        RR_angle = int(RR_angle)+90
        RL_angle = int(RL_angle)+90
        self.get_logger().info(f"FR: {FR_angle}")
        self.get_logger().info(f"FL: {FL_angle}")
        self.get_logger().info(f"RR: {RR_angle}")
        self.get_logger().info(f"RL: {RL_angle}")

        data = bytes([0xAA, FL_angle, FR_angle, RL_angle, RR_angle, speed])
        try:
            ser.write(bytes(data))
            self.get_logger().info(f"Sent: {bytes([0xAA, FL_angle, FR_angle, RR_angle, RL_angle, speed])}")
        except:
            self.get_logger().info("Unable to write bytes, flushing")
            ser.reset_output_buffer()

def main(args=None):
    rclpy.init(args=args)
    node = SteeringControl()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
