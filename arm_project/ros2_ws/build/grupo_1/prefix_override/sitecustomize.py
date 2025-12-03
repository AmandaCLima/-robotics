import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/CIN/tjgc/Documents/Robotics/ros2_ws/install/grupo_1'
