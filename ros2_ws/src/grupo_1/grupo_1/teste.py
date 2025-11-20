from robot import Robot
import numpy as np
import math as m
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

# # Validate the kinematics operations:
# # Encontrar o ponto usando os ângulos
# rotation = [0, 0, 0, 0]
# print(f'Original angles: {rotation}')
# result1 = rob.forward_kinematics(rotation)
# print(f'Test Forward: {result1}')

# # Usar o ponto encontrado e a orientação para retornar os ângulos usados:
# angles = rob.inverse_kinematics(result1)

# dist1 = np.sum(np.abs(angles[:, 0] - rotation))
# dist2 = np.sum(np.abs(angles[:, 1] - rotation))
# if dist1 < dist2:
#     angles = angles[:, 0]
# else:
#     angles = angles[:, 1]

# print(f'Test Inverse: {angles}')


# # Usar os angulos retornados para verificar se chega no mesmo ponto
# result2 = rob.forward_kinematics(angles)
# print(f'Test Forward: {result2}')
# print(result1.round(10) == result2.round(10))

# # Validate the trajectory operations:
# pose_final = [13.45, 13.45, 30.48, 65]
# juntas_inicial = [0, 90, -90, 0]  # Pose fictícia

# t_total, qs, qd, qdd = rob.joint_space_trajectory(juntas_inicial, pose_final)

pose_final = [13.45, 13.45, 30.48, 65]
pose_inicial = [27.8,  0.,  11.2,  0.]  # Pose fictícia
num_points = 10000
t_total, poses, qs, qd, qdd = rob.task_space_trajectory(pose_inicial, pose_final, 15, num_points)

# O array 'poses' deve ter a forma (N_pontos, 4) onde as colunas são (x, y, z, phi)

task_labels = ['Posição X', 'Posição Y', 'Posição Z', 'Orientação Phi (Graus)']
task_units = ['(unidades de distância)', '(unidades de distância)', '(unidades de distância)', '(graus)']

# --- Posição Cartesiana (X, Y, Z e Phi) ---
plt.figure(figsize=(10,6))
for i in range(4): # Loop sobre as 4 coordenadas (x, y, z, phi)
    # Assumindo que poses é a matriz cartesiana (N_pontos x 4)
    plt.plot(t_total, poses[:, i], label=task_labels[i]) 
    
plt.title("Posição e Orientação no Espaço da Tarefa")
plt.xlabel("Tempo (s)")
# Nota: O eixo Y tem unidades mistas (distância e ângulo), então o rótulo é geral.
plt.ylabel(f"Valor ({task_units[0]} ou {task_units[3]})") 
plt.legend()
plt.grid(True)
plt.show()

# --- Plot separado para as coordenadas (opcional, para melhor visualização) ---
plt.figure(figsize=(10,6))
for i in range(3): # Apenas X, Y, Z
    plt.plot(t_total, ((np.cos(np.linspace(-m.pi, 0, num_points)) + 1) / 2), label=task_labels[i])
plt.title("Coordenadas Cartesianas (X, Y, Z) no Tempo")
plt.xlabel("Tempo (s)")
plt.ylabel("Posição (unidades de distância)")
plt.legend()
plt.grid(True)
plt.show()

# --- Posições, Velocidades e Acelerações das Juntas ---

labels = [f'Junta {i+1}' for i in range(num_joints)]
plt.figure(figsize=(10,6))
for i in range(num_joints):
    plt.plot(t_total, qs[:,i], label=labels[i])
plt.title("Posição das Juntas")
plt.xlabel("Tempo (s)")
plt.ylabel("Posição (rad ou m)")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10,6))
for i in range(num_joints):
    plt.plot(t_total, qd[:,i], label=labels[i])
plt.title("Velocidade das Juntas")
plt.xlabel("Tempo (s)")
plt.ylabel("Velocidade (rad/s ou m/s)")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10,6))
for i in range(num_joints):
    plt.plot(t_total, qdd[:,i], label=labels[i])
plt.title("Aceleração das Juntas")
plt.xlabel("Tempo (s)")
plt.ylabel("Aceleração (rad/s² ou m/s²)")
plt.legend()
plt.grid(True)
plt.show()