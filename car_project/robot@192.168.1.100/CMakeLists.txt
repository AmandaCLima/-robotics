cmake_minimum_required(VERSION 3.8)
project(lidar)

# Boas práticas de compilação
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Encontrar dependências gerais
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)     
find_package(tf2_ros REQUIRED)
find_package(ydlidar_sdk REQUIRED)

# Inclusão de diretórios (SDK do YDLidar)
include_directories(
  include
  /usr/local/include
  /usr/local/include/src
)

# =========================================================
# ALVO 1: O Driver do LiDAR (Publisher)
# =========================================================
# Nota: Mantive lidar_teste.cpp na raiz conforme seu último código
add_executable(lidar_teste lidar_teste.cpp)

ament_target_dependencies(lidar_teste
  rclcpp
  sensor_msgs
  tf2
  tf2_ros
)

target_link_libraries(lidar_teste 
  ydlidar_sdk
  pthread # Recomendado para garantir estabilidade das threads do driver
)

# =========================================================
# ALVO 2: O Leitor de Dados (Subscriber)
# =========================================================
# Nota: Assumindo que você criou este arquivo dentro da pasta 'src'
add_executable(lidar_listener src/lidar_listener.cpp)

ament_target_dependencies(lidar_listener
  rclcpp
  sensor_msgs
)
# O listener não precisa linkar a ydlidar_sdk pois só usa mensagens ROS padrão

# =========================================================
# Instalação (Instalar AMBOS os executáveis)
# =========================================================
install(TARGETS 
  lidar_teste 
  lidar_listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()