import sys 
import rclpy
from arm_interfaces.srv import FollowTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from rclpy.node import Node
from builtin_interfaces.msg import Duration


import numpy as np
import math as m

class Robot():
    def __init__(self, distances, tool_distance_from_last_motor, v_max, a_max, num_joints=4):
        self.distances = distances
        self.tool_distance_from_last_motor = tool_distance_from_last_motor
        self.num_joints = num_joints
        self.v_max = v_max
        self.a_max = a_max

    def forward_kinematics(self, angles):
        # Tool point transformation to basis reference
        T = (self._Tz(self.distances[0])
             @ self._Rz(angles[0]) @ self._Tz(self.distances[1])
             @ self._Ry(angles[1]) @ self._Tx(self.distances[2])
             @ self._Ry(angles[2]) @ self._Tx(self.distances[3])
             @ self._Ry(angles[3]))
        point = T @ self.tool_distance_from_last_motor
        tool_angle = self._compute_q0(point[0,0], point[1,0])
        orientation = angles[1] + angles[2] + angles[3]

        # Normalize the angles to the range [-180, 180]
        q1_norm = (angles[0] + 180) % 360 - 180
        tool_angle_norm = (tool_angle + 180) % 360 - 180

        # Adjust orientation if the arm is "flipped" (180 degrees difference in Yaw)
        angle_diff = abs(tool_angle_norm - q1_norm)
        if angle_diff > 179.9 or angle_diff < -179.9:
            orientation = 180 - orientation

        pose = np.array([point[0,0], point[1,0], point[2,0], orientation])
        return pose

    def inverse_kinematics(self, pose):
        [x, y, z, phi] = pose # Pose of the tool
        z = z - (self.distances[0] + self.distances[1]) # Adjusting z to the first motor above the base

        # Coordinates of the motor before the tool
        q0 = self._compute_q0(x, y)
        r_tool = m.sqrt(x**2 + y**2)
        z_last_motor = z - (self.tool_distance_from_last_motor[0,0] * m.sin(m.radians(phi))) # Getting the value of the Z axis on RZ plane where the motor is located
        r_last_motor = r_tool - (self.tool_distance_from_last_motor[0, 0] * m.cos(m.radians(phi))) # Getting the value of the R axis on RZ plane where the motor is located

        # Getting the angles
        # Tries to compute q2, if not possible, exits the function
        try:
            q2 = self._compute_q2(r_last_motor, z_last_motor, self.distances[2], self.distances[3])
        except Exception: # Boa prática é capturar a exceção específica
            return None

        # Selects the best solution for q2 and computes q1 accordingly (if both are valid then selects the one with smaller absolute value for q1)
        q1 = []
        q1.append(self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2[0]))
        q1.append(self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2[1]))
        print(f"q1_positive: {q1[0]}, q1_negative: {q1[1]}")
        print(f"q2_positive: {q2[0]}, q2_negative: {q2[1]}")

        # Computes q3 based on desired orientation phi
        q3 = phi - (q1 + q2)
        print(f"q3_positive: {q3[0]}, q3_negative: {q3[1]}")

        return np.array([q0, q1, q2, q3])

    def joint_space_trajectory(self, pose_final=0, pose_inicial=0, dt=0.02):
        #q_init = self.inverse_kinematics(pose_inicial)
        #q_fim = self.inverse_kinematics(pose_final)

        q_init = [0, 90, -90, 0]
        q_fim = [90, 90, -30, -60]

        if q_init is None or q_fim is None:
            raise ValueError("Posição inicial ou final inalcançável")

        print("Initial joints position:", q_init)
        print("Final joints position:", q_fim)

        # Find the maximum time required among all joints
        times_total = []
        for i in range(self.num_joints):
            if q_init[i] == q_fim[i]:
                times_total.append(0)
            else:
                t_total_joint = self._calculate_t_total(q_init[i], q_fim[i], self.v_max[i], self.a_max[i])
                times_total.append(t_total_joint)

        T_sync = max(times_total) # Total synchronized time

        # If T_sync is zero, return initial positions only (no movement)
        if T_sync == 0:
            t_total = np.array([0])
            qs = q_init.reshape(1, -1)
            qd = np.zeros_like(qs)
            qdd = np.zeros_like(qs)
            return t_total, qs, qd, qdd

        print(f"Synchronizing movement for: {T_sync:.3f} seconds")

        # Generate trajectories for each joint based on T_sync
        qs_list = []

        # The number of points must be the same for all
        num_points = int(round(T_sync / dt)) + 1
        t_total = np.linspace(0, T_sync, num_points) # This is the final time vector

        for i in range(self.num_joints):
            if q_init[i] == q_fim[i]:
                # Joint doesn't move: just repeat the position
                q = np.full(num_points, q_init[i])
            else:
                q = self._trapezoidal_profile(q_init[i], q_fim[i], self.a_max[i], T_sync, t_total)

            qs_list.append(q)

        # Convert to array (rows: time, columns: joints)
        qs = np.vstack(qs_list).T

        # Calculate velocity and acceleration
        qd = np.gradient(qs, dt, axis=0)   # velocity
        qdd = np.gradient(qd, dt, axis=0)  # acceleration

        return t_total, qs, qd, qdd

    def _trapezoidal_profile(self, q0, qf, amax, T_sync, t):
        dq = qf - q0

        # Solve the quadratic equation to find the required v_scaled
        # (1/amax) * v_new**2 - T_sync * v_new + abs(dq) = 0

        if amax == 0: return np.full_like(t, qf)

        discriminant = T_sync**2 - 4 * abs(dq) / amax

        # If the discriminant is negative, T_sync is too short (triangular profile)
        if discriminant < 0:
            discriminant = 0

        # We want the *smaller* velocity solution that works
        v_scaled = (amax / 2) * (T_sync - np.sqrt(discriminant))

        # For safety, v_scaled cannot be 0 if there is movement
        if v_scaled == 0 and dq != 0:
             # This happens if T_sync = 0, which is already handled, but for safety:
             if T_sync > 0: 
                 v_scaled = 2 * abs(dq) / T_sync # Triangular profile
             else: 
                return np.full_like(t, qf)

        t_acc = v_scaled / amax
        d_acc = 0.5 * amax * t_acc**2
        t_cte = T_sync - 2 * t_acc

        # If t_cte is negative (floating point error), adjust to triangular
        if t_cte < 0:
            t_acc = T_sync / 2
            t_cte = 0
            # Recalculate v_scaled and a_scaled for the triangular profile
            a_scaled = 4 * abs(dq) / (T_sync**2)
            v_scaled = a_scaled * t_acc
            d_acc = abs(dq) / 2
            amax = a_scaled

        q = np.zeros_like(t)

        for i, ti in enumerate(t):
            if ti < t_acc:
                q[i] = q0 + 0.5 * amax * ti**2 * np.sign(dq)
            elif ti < (t_acc + t_cte):
                q[i] = q0 + (d_acc + v_scaled * (ti - t_acc)) * np.sign(dq)
            else:
                td = ti - t_acc - t_cte
                q[i] = qf - 0.5 * amax * (t_acc - td)**2 * np.sign(dq)

        # Guarantee that the last point is *exactly* the end
        if len(q) > 0:
            q[-1] = qf

        return q

    def _calculate_t_total(self, q0, qf, vmax, amax):
        dq = qf - q0

        # Protection against zero vmax or amax
        if amax == 0 or vmax == 0:
            if dq == 0: 
                return 0 
            else:
                return float('inf')

        t_acc = vmax / amax
        d_acc = 0.5 * amax * t_acc**2

        # If the displacement is too small to reach vmax (triangular profile)
        if abs(dq) < 2 * d_acc:
            t_acc = np.sqrt(abs(dq) / amax)
            t_cte = 0
        else: # Trapezoidal profile
            d_cte = abs(dq) - 2 * d_acc
            t_cte= d_cte / vmax

        t_total = 2 * t_acc + t_cte
        return t_total

    def _Rz(self, theta):
        theta = m.radians(theta)
        c = m.cos(theta)
        s = m.sin(theta)
        transform = np.array([[c, -s, 0, 0],
                            [s,  c, 0, 0],
                            [0,  0, 1, 0],
                            [0,  0, 0 ,1]])
        return transform

    def _Ry(self, theta):
        theta = m.radians(theta)
        c = m.cos(theta)
        s = m.sin(theta)
        transform = np.array([[c, 0, -s, 0],
                            [0, 1,  0, 0],
                            [s, 0,  c, 0],
                            [0, 0,  0, 1]])
        return transform

    def _Tx(self, distance):
        transform = np.array([[1, 0, 0, distance],
                            [0, 1, 0, 0],
                            [0, 0, 1, 0],
                            [0, 0, 0, 1]])
        return transform

    def _Tz(self, distance):
        transform = np.array([[1, 0, 0, 0],
                            [0, 1, 0, 0],
                            [0, 0, 1, distance],
                            [0, 0, 0, 1]])
        return transform

    def _compute_q0(self, x, y):
        q0 = m.atan2(y, x)
        return m.degrees(q0)

    def _compute_q2(self, r, z, a1, a2):
        aux = (r**2 + z**2 - a1**2 - a2**2) / (2 * a1 * a2)
        if aux > 1 or aux < -1:
            raise ValueError("Position unreachable")
        q2 = m.acos(aux)
        return [m.degrees(q2), m.degrees(-q2)]

    def _compute_q1(self, r, z, a1, a2, q2):
        q2 = m.radians(q2)
        q1 = m.atan2(z, r) - m.atan2((a2*m.sin(q2)), (a1+(a2*m.cos(q2))))
        return m.degrees(q1)


class MinimalClientAsync(Node):
    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(FollowTrajectory, 'moveServer/followTrajectory_srv')
        while not self.cli.wait_for_service(timeout_sec = 1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = FollowTrajectory.Request()

    def send_request(self, pos, time):
        self.req.data.points = []
        for idx in range(len(pos)):
            pt = JointTrajectoryPoint()
            pt.positions = [0] * 4
            pt.positions[0] = pos[idx][0]
            pt.positions[1] = pos[idx][1]
            pt.positions[2] = pos[idx][2]
            pt.positions[3] = pos[idx][3]
            pt.time_from_start = Duration(sec=int(time[idx]), nanosec=int((time[idx] % 1) * 1e9))
            self.req.data.points.append(pt)
        print('Calling service...')
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


# class MinimalClientAsync(Node):
#     def __init__(self):
#         super().__init__('minimal_client_async')
#         self.cli = self.create_client(FollowTrajectory, 'moveServer/followTrajectory_srv')
#         while not self.cli.wait_for_service(timeout_sec = 1.0):
#             self.get_logger().info('service not available, waiting again...')
#         print("Conectou !!")

# def main():
#     rclpy.init()
#     minimal_client = MinimalClientAsync()
#     future = minimal_client.send_request(int(sys.argv[1]), int(sys.argv[2]))
#     rclpy.spin_until_future_complete(minimal_client, future)
#     response = future.result()
#     #minimal_client.get_logger().info('Result of add_two_ints: for %d + %d = %d' % (int(sys.argv[1]), int(sys.argv[2]), response.sum))

#     minimal_client.destroy_node()
#     rclpy.shutdown()


if __name__ == '__main__':
    main()
