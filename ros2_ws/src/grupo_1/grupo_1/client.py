from robot import Robot
import sys 
import rclpy
from arm_interfaces.srv import FollowTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoints
from rclpy.node import Node
import numpy as np

class MinimalClientAsync(Node):
    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(FollowTrajectory, 'moveServer/followTrajectory_srv')
        while not self.cli.wait_for_service(timeout_sec = 1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = FollowTrajectory.Request()

    def send_request(self, pos, time):
        self.req.data.points.positions = pos
        self.req.data.points.time_from_start = time
        self.cli.call_async(self.req)
    
def main():
    tool_point = np.array([[0.052],
                      [0],
                      [0],
                      [1]])
    translation = [0, 0.112, 0.103, 0.123]
    v_max = [30, 30, 30, 30]
    a_max = [10, 10, 10, 10]
    num_joints = 4
    # pose_final = [13.45, 13.45, 30.48, 65] # Pose fictícia
    # pose_inicial = [27.8, 0, 11.2, 0]  # Pose fictícia
    rob = Robot(translation, tool_point, v_max, a_max, num_joints)
    dt, pos, _, _ = rob.joint_space_trajectory()
    # int(sys.argv[1]), int(sys.argv[2])
    rclpy.init()
    minimal_client = MinimalClientAsync()
    future = minimal_client.send_request(pos, dt)
    rclpy.spin_until_future_complete(minimal_client, future)
    # minimal_client.get_logger().info('Result of add_two_ints: for %d + %d = %d' % (int(sys.argv[1]), int(sys.argv[2]), response.sum))

    minimal_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
