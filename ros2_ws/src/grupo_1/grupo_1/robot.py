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
        tool_xy_angle = self._compute_q0(point[0,0], point[1,0])
        orientation = angles[1] + angles[2] + angles[3]

        # Normalize the angles to the range [-180, 180]
        q1_norm = (angles[0] + 180) % 360 - 180
        tool_xy_angle_norm = (tool_xy_angle + 180) % 360 - 180

        # Asjust orientation if the arm is "flipped" (180 degrees difference in Yaw)
        angle_diff = abs(tool_xy_angle_norm - q1_norm)
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
        except:
            return
        
        # Selects the best solution for q2 and computes q1 accordingly (if both are valid then selects the one with smaller absolute value for q1)
        if -90 <= q2[0] <= 90 and -90 <= q2[1] <= 90:
            q1_positive = self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2[0])
            q1_negative = self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2[1])
            if abs(q1_positive) <= abs(q1_negative):
                q2 = q2[0]
                q1 = q1_positive
            else:
                q2 = q2[1]
                q1 = q1_negative

        elif -90 <= q2[0] <= 90:
            q2 = q2[0]
            q1 = self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2)

        else:
            q2 = q2[1]
            q1 = self._compute_q1(r_last_motor, z_last_motor, self.distances[2], self.distances[3], q2)
        
        # Computes q3 based on desired orientation phi
        q3 = phi - (q1 + q2)

        return np.array([q0, q1, q2, q3])

    def joint_space_trajectory(self, pose_final, pose_inicial, dt=0.005):
        q_init = self.inverse_kinematics(pose_inicial)
        q_fim = self.inverse_kinematics(pose_final)

        print("Posição inicial das juntas:", q_init)
        print("Posição final das juntas:", q_fim)

        traj = []
        times = []

        for i in range(self.num_joints):
            if q_init[i] == q_fim[i]:
                t = np.array([0])
                q = np.array([q_init[i]])
            else:
                t, q = self._trapezoidal_profile(q_init[i], q_fim[i], self.v_max[i], self.a_max[i], dt)
            traj.append(q)
            times.append(t)

        t_total = max(times, key=len)

        # Interpolação
        qs = [np.interp(t_total, times[i], traj[i]) for i in range(self.num_joints)]

        # Converter em array (linhas: tempo, colunas: juntas)
        qs = np.vstack(qs).T

        # Calcular velocidade e aceleração por diferenças finitas
        qd = np.gradient(qs, dt, axis=0)   # velocidade
        qdd = np.gradient(qd, dt, axis=0)  # aceleração

        return t_total, qs, qd, qdd

    def _trapezoidal_profile(self, q0, qf, vmax, amax, dt):
        dq = qf - q0
        t_acc = vmax / amax
        d_acc = 0.5 * amax * t_acc**2

        # Caso em que o deslocamento é pequeno demais para atingir vmax
        if abs(dq) < 2 * d_acc:
            t_acc = np.sqrt(abs(dq) / amax)
            t_cte = 0
        else:
            d_cte = abs(dq) - 2 * d_acc
            t_cte= d_cte / vmax

        t_total = 2 * t_acc + t_cte
        t = np.arange(0, t_total, dt)
        q = np.zeros_like(t)

        for i, ti in enumerate(t):
            if ti < t_acc:
                q[i] = q0 + 0.5 * amax * ti**2 * np.sign(dq)
            elif ti < (t_acc + t_cte):
                q[i] = q0 + (d_acc + vmax * (ti - t_acc)) * np.sign(dq)
            else:
                td = ti - t_acc - t_cte
                q[i] = qf - 0.5 * amax * (t_acc - td)**2 * np.sign(dq)

        return t, q

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