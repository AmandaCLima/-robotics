from robot import Robot
import numpy as np


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