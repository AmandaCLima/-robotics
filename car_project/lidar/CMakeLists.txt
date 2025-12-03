cmake_minimum_required(VERSION 3.5)
project(lidar)

set(CMAKE_CXX_STANDARD 14)

find_package(ydlidar_sdk REQUIRED)

add_executable(lidar lidar.cpp)

target_link_libraries(lidar ylidar_sdk)