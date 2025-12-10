cmake_minimum_required(VERSION 3.5)
project(lidar_test)

set(CMAKE_CXX_STANDARD 14)

find_package(ydlidar_sdk REQUIRED)

add_executable(lidar_teste lidar_test.cpp)

target_link_libraries(lidar_test ylidar_sdk)