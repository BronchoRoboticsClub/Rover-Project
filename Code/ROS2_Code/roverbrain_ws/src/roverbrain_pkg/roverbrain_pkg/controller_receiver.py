import rclpy
from rclpy.node import Node
from rover_interfaces.msg import Control
import serial



class ControllerReceiver(Node):
    def __init__(self):
        super().__init__("receiver")
        self.subscriber_ = self.create_subscription(Control, "controller", self.handle_received_inputs, 10)
        self.get_logger().info("Receiver node has started")

    def handle_received_inputs(self, msg: Control):
        self.get_logger().info(f"{msg.speed} {msg.steering_angle}")



def main(args=None):
    rclpy.init(args=args)
    node = ControllerReceiver()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()