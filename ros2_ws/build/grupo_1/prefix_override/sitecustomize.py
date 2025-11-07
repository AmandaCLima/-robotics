import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/CIN/acfml/Robotics/ros2_ws/install/grupo_1'
