import numpy as np
import math as m

# Base motor: rotation in Z, other motors: rotations in Y.
# Translations: X and Z.
# Forward Kinematics
# Creation of the transformation class:

class Transform():
  def __init__(self):
    return

  def transform(self, T, R, tool_point):
    if(len(T) < 4 or len(R) < 4):
      print('Error')
    t = self._Tz(T[0]) @ self._Rz(R[0]) @ self._Tz(T[1]) @ self._Ry(R[1]) @ self._Tx(T[2]) @ self._Ry(R[2]) @ self._Tx(T[3]) @ self._Ry(R[3]) @ tool_point
    return t.round(5)

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

"""Tests for forward kinematics using the equation: 
Tz @ Rz @ Tz @ Ry @ Tx @ Ry @ Tx @ Ry @ tool point relative to the last motor.
For testing purposes, the tool point will be [5, 0, 0] (distance 5 in x from the last motor)
"""

# Forward Kinematics
t = Transform()
tool_point = np.array([[5],
                      [0],
                      [0],
                      [1]])
translation = [5, 5, 5, 5]

# First test: zero state
rotation = [0, 0, 0, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 1: {result}', end='\n\n')

# Second test: standing
rotation = [0, 90, 0, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 2: {result}', end='\n\n')

# Third test: zero state rotated to Y
rotation = [90, 0, 0, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 3: {result}', end='\n\n')

# Fourth tests: 45 degrees in each joint
rotation = [45, 0, 0, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 4.1: {result}', end='\n\n')

rotation = [0, 45, 0, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 4.2: {result}', end='\n\n')

rotation = [0, 0, 45, 0]
result = t.transform(translation, rotation, tool_point)
print(f'Test 4.3: {result}', end='\n\n')

rotation = [0, 0, 0, 45]
result = t.transform(translation, rotation, tool_point)
print(f'Test 4.4: {result}', end='\n\n')

## Inverse Kinematics
class GetRotation():
  def __init__(self):
    return

  # pose: X, Y, Z, theta (point and orientation) -> Orientation is in the global reference
  def get_angles(self, pose, T, motor_tool_distance):
    [x, y, z, phi] = pose # Tool pose
    z = z - (T[0]+T[1]) # Adjusting z to the first motor above the base
    r = m.sqrt(x**2 + y**2) # Getting the value of the R axis on RZ plane where the point is located

    # Coordinates of the motor before the tool on RZ plane
    motor_z = z - motor_tool_distance * m.sin(m.radians(phi))
    motor_r = r - motor_tool_distance * m.cos(m.radians(phi))

    # Getting the angles
    base = self._rotate_base(x, y)
    q2 = self._rotate_second_joint(motor_r, motor_z, T[2], T[3])
    q1 = self._rotate_first_joint(motor_r, motor_z, T[2], T[3], q2)
    orientation = phi - (q1 + q2)
    return np.array([base, q1, q2, orientation])

  def _rotate_base(self, x, y):
    base = m.atan2(y, x)
    return m.degrees(base)

  def _rotate_second_joint(self, r, z, a1, a2):
    q2 = m.acos((r**2 + z**2 - a1**2 - a2**2) / (2 * a1 * a2))
    return m.degrees(q2)

  def _rotate_first_joint(self, r, z, a1, a2, q2):
    q2 = m.radians(q2)
    q1 = m.atan2(z, r) - m.atan2((a2*m.sin(q2)), (a1+(a2*m.cos(q2))))
    return m.degrees(q1)

# Validate with the points of the first tests (Forward Kinematics)
rotate = GetRotation()
T = [5, 5, 5, 5]

pose = [15, 0, 10, 0]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 1: {angles.round(1)}', end='\n\n')

pose = [0, 0, 25, 90]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 2: {angles.round(1)}', end='\n\n')

pose = [0, 15, 10, 0]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 3: {angles.round(1)}', end='\n\n')

pose = [10.6066, 10.6066, 10, 0]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 4.1: {angles.round(1)}', end='\n\n')

pose = [10.6066, 0, 20.6066, 45]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 4.2: {angles.round(1)}', end='\n\n')

pose = [12.07107, 0, 17.07107, 45]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 4.3: {angles.round(1)}', end='\n\n')

pose = [13.53553, 0, 13.53553, 45]
angles = rotate.get_angles(pose, T, 5)
print(f'Test 4.4: {angles.round(1)}', end='\n\n')

# Validate both functions

# Validate the operations:
t = Transform()
rotate = GetRotation()
tool_point = np.array([[5],
                      [0],
                      [0],
                      [1]])
translation = [5, 5, 5, 5]

# Find the point using the angles
rotation = [28, 63, 29, 14]
print(f'Original angles: {rotation}')
result = t.transform(translation, rotation, tool_point)
print(f'Test Forward: {result}')

# Use the found point and orientation to return the used angles:
pose = [result[0][0], result[1][0], result[2][0], rotation[1] + rotation[2] + rotation[3]]
angles = rotate.get_angles(pose, translation, tool_point[0][0])
print(f'Test Inverse: {angles.round(1)}')
