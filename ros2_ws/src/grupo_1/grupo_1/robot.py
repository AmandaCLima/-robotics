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

        # Asjust orientation if the arm is "flipped" (180 degrees difference in Yaw)
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

        if q_init is None or q_fim is None:
            print("Erro: Cinemática Inversa falhou. Posição inalcançável.")
            return None, None, None, None

        print("Posição inicial das juntas:", q_init)
        print("Posição final das juntas:", q_fim)

        # --- ETAPA 1: Encontrar o tempo de sincronização ---
        times_total = []
        for i in range(self.num_joints):
            if q_init[i] == q_fim[i]:
                times_total.append(0)
            else:
                t_total_joint = self._calculate_t_total(q_init[i], q_fim[i], self.v_max[i], self.a_max[i])
                times_total.append(t_total_joint)

        T_sync = max(times_total) # Tempo mestre (o mais lento)

        # Se T_sync for 0 (sem movimento), retorne imediatamente
        if T_sync == 0:
            t_total = np.array([0])
            qs = q_init.reshape(1, -1) # Uma linha
            qd = np.zeros_like(qs)
            qdd = np.zeros_like(qs)
            return t_total, qs, qd, qdd

        print(f"Sincronizando movimento para: {T_sync:.3f} segundos")

        # --- ETAPA 2: Gerar trajetórias escalonadas (sem interpolação!) ---
        qs_list = []

        # O número de pontos deve ser o mesmo para todos
        num_points = int(round(T_sync / dt)) + 1
        t_total = np.linspace(0, T_sync, num_points) # Este é o vetor de tempo final

        for i in range(self.num_joints):
            if q_init[i] == q_fim[i]:
                # Junta parada: apenas repita a posição
                q = np.full(num_points, q_init[i])
            else:
                # --- MUDANÇA AQUI ---
                # Gere o perfil forçando o T_sync
                # Note que passamos self.a_max[i]
                q = self._trapezoidal_profile_scaled(q_init[i], q_fim[i],
                                                    self.a_max[i], T_sync, t_total)
                # --- FIM DA MUDANÇA ---

            qs_list.append(q)

        # Converter em array (linhas: tempo, colunas: juntas)
        qs = np.vstack(qs_list).T

        # Calcular velocidade e aceleração
        qd = np.gradient(qs, dt, axis=0)   # velocidade
        qdd = np.gradient(qd, dt, axis=0)  # aceleração

        return t_total, qs, qd, qdd

    # --- FUNÇÃO NOVA / CORRIGIDA ---
    # Esta é a função que você realmente precisa
    def _trapezoidal_profile_scaled(self, q0, qf, amax, T_sync, t):
        """
        Calcula um perfil trapezoidal escalonado para um T_sync fixo.
        Ele recalcula a velocidade necessária (v_scaled) assumindo a amax da junta.
        """
        dq = qf - q0

        # Resolve a equação quadrática para encontrar a v_scaled necessária
        # (1/amax) * v_new**2 - T_sync * v_new + abs(dq) = 0

        # Proteção contra divisão por zero ou valores inválidos
        if amax == 0: return np.full_like(t, qf)

        discriminant = T_sync**2 - 4 * abs(dq) / amax

        # Se o discriminante for negativo, T_sync é muito curto (o que não deve acontecer)
        # Isso significa que nem mesmo amax é suficiente, o que é um erro de lógica
        # Mas, por segurança, vamos tratar como um perfil triangular
        if discriminant < 0:
            # print("Aviso: T_sync é menor que o tempo triangular. Ajustando.")
            discriminant = 0

        # Queremos a solução de velocidade *menor* que funciona
        v_scaled = (amax / 2) * (T_sync - np.sqrt(discriminant))

        # Por segurança, v_scaled não pode ser 0 se houver movimento
        if v_scaled == 0 and dq != 0:
             # Isso acontece se T_sync = 0, o que já é tratado, mas por segurança:
             if T_sync > 0: v_scaled = 2 * abs(dq) / T_sync # Perfil triangular
             else: return np.full_like(t, qf)

        # Agora temos os parâmetros escalonados
        t_acc = v_scaled / amax
        d_acc = 0.5 * amax * t_acc**2
        t_cte = T_sync - 2 * t_acc

        # Se t_cte for negativo (erro de ponto flutuante), ajuste para triangular
        if t_cte < 0:
            t_acc = T_sync / 2
            t_cte = 0
            # Recalcula v_scaled e a_scaled para o perfil triangular
            a_scaled = 4 * abs(dq) / (T_sync**2)
            v_scaled = a_scaled * t_acc
            d_acc = abs(dq) / 2
            amax = a_scaled # Use a aceleração escalonada no cálculo abaixo

        q = np.zeros_like(t)

        for i, ti in enumerate(t):
            if ti < t_acc:
                q[i] = q0 + 0.5 * amax * ti**2 * np.sign(dq)
            elif ti < (t_acc + t_cte):
                q[i] = q0 + (d_acc + v_scaled * (ti - t_acc)) * np.sign(dq)
            else:
                td = ti - t_acc - t_cte
                q[i] = qf - 0.5 * amax * (t_acc - td)**2 * np.sign(dq)

        # Garanta que o último ponto seja *exatamente* o final
        if len(q) > 0:
            q[-1] = qf

        return q
    # --- FIM DA FUNÇÃO NOVA ---

    def _calculate_t_total(self, q0, qf, vmax, amax):
        # Esta função está correta e é usada por joint_space_trajectory
        dq = qf - q0

        # Proteção contra divisão por zero
        if amax == 0 or vmax == 0:
            return 0 if dq == 0 else float('inf')

        t_acc = vmax / amax
        d_acc = 0.5 * amax * t_acc**2

        # Caso em que o deslocamento é pequeno demais para atingir vmax (perfil triangular)
        if abs(dq) < 2 * d_acc:
            t_acc = np.sqrt(abs(dq) / amax)
            t_cte = 0
        else: # Perfil trapezoidal
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