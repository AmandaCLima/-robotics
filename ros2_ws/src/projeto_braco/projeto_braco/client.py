from robot import Robot
import sys 
import rclpy
from arm_interfaces_srv import FollowTrajectory 
from rclpy.node import Node
import numpy as np

class MinimalClientAsync(Node):
    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(FollowTrajectory, 'Follow Trajectory')
        while not self.cli.wait_for_service(timeout_sec = 1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = FollowTrajectory.Request()

    def send_request(self, pos):
        self.pos = pos
        self.cli.call_async(self.pos)
    
def main():
    tool_point = np.array([[5.2],
                      [0],
                      [0],
                      [1]])
    translation = [0, 11.2, 10.3, 12.3]
    v_max = [30, 30, 30, 30]
    a_max = [15, 15, 15, 15]
    num_joints = 4
    pose_final = [13.45, 13.45, 30.48, 65] # Pose fictícia
    pose_inicial = [27.8, 0, 11.2, 0]  # Pose fictícia
    rob = Robot(translation, tool_point, v_max, a_max, num_joints)
    _, pos, _, _ = rob.joint_space_trajectory(pose_final, pose_inicial)
    # int(sys.argv[1]), int(sys.argv[2])
    rclpy.init()
    minimal_client = MinimalClientAsync()
    future = minimal_client.send_request(pos)
    rclpy.spin_until_future_complete(minimal_client, future)
    response = future.result()
    # minimal_client.get_logger().info('Result of add_two_ints: for %d + %d = %d' % (int(sys.argv[1]), int(sys.argv[2]), response.sum))

    minimal_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
