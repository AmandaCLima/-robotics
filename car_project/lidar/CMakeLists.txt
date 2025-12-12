cmake_minimum_required(VERSION 3.0.2)
project(ydlidar_ros_driver)

# Busca dependências do ROS
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  tf
)

# Busca a biblioteca YDLidar SDK
find_library(YDLIDAR_SDK_LIB ydlidar_sdk
  PATHS /usr/local/lib
        ${CMAKE_INSTALL_PREFIX}/lib
        ${PROJECT_SOURCE_DIR}/../YDLidar-SDK/build
  REQUIRED
)

find_path(YDLIDAR_SDK_INCLUDE ydlidar_sdk.h
  PATHS /usr/local/include
        ${CMAKE_INSTALL_PREFIX}/include
        ${PROJECT_SOURCE_DIR}/../YDLidar-SDK/include
  REQUIRED
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp sensor_msgs tf
)

include_directories(
  include
  ${YDLIDAR_SDK_INCLUDE}
  ${catkin_INCLUDE_DIRS}
)

# Executável principal
add_executable(ydlidar_node src/ydlidar_node.cpp)
target_link_libraries(ydlidar_node
  ${catkin_LIBRARIES}
  ${YDLIDAR_SDK_LIB}
)

# Instalação
install(TARGETS ydlidar_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install(DIRECTORY launch/
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
# )

# install(DIRECTORY config/
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
# )

# install(DIRECTORY rviz/
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/rviz
# )