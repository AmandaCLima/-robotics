from robot import Robot
import numpy as np
import matplotlib.pyplot as plt


tool_point = np.array([[5.2],
                      [0],
                      [0],
                      [1]])
translation = [0, 11.2, 10.3, 12.3]
v_max = [30, 30, 30, 30]
a_max = [15, 15, 15, 15]
num_joints = 4
rob = Robot(translation, tool_point, v_max, a_max, num_joints)

# Validate the kinematics operations:
# Encontrar o ponto usando os ângulos
rotation = [0, 90, -60, 0]
print(f'Original angles: {rotation}')
result1 = rob.forward_kinematics(rotation)
print(f'Test Forward: {result1}')

# Usar o ponto encontrado e a orientação para retornar os ângulos usados:
angles = rob.inverse_kinematics(result1)
print(f'Test Inverse: {angles}')

# Usar os angulos retornados para verificar se chega no mesmo ponto
result2 = rob.forward_kinematics(angles)
print(f'Test Forward: {result2}')
print(result1.round(10) == result2.round(10))

# # Validate the trajectory operations:
# pose_final = [13.45, 13.45, 30.48, 65]
# pose_inicial = [27.8, 0, 11.2, 0]  # Pose fictícia

# t_total, qs, qd, qdd = rob.joint_space_trajectory(pose_final, pose_inicial)

# print(qs[0])
# print(t_total)

# labels = [f'Junta {i+1}' for i in range(num_joints)]
# plt.figure(figsize=(10,6))
# for i in range(num_joints):
#     plt.plot(t_total, qs[:,i], label=labels[i])
# plt.title("Posição das Juntas")
# plt.xlabel("Tempo (s)")
# plt.ylabel("Posição (rad ou m)")
# plt.legend()
# plt.grid(True)
# plt.show()

# plt.figure(figsize=(10,6))
# for i in range(num_joints):
#     plt.plot(t_total, qd[:,i], label=labels[i])
# plt.title("Velocidade das Juntas")
# plt.xlabel("Tempo (s)")
# plt.ylabel("Velocidade (rad/s ou m/s)")
# plt.legend()
# plt.grid(True)
# plt.show()

# plt.figure(figsize=(10,6))
# for i in range(num_joints):
#     plt.plot(t_total, qdd[:,i], label=labels[i])
# plt.title("Aceleração das Juntas")
# plt.xlabel("Tempo (s)")
# plt.ylabel("Aceleração (rad/s² ou m/s²)")
# plt.legend()
# plt.grid(True)
# plt.show()