#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <cmath>     // Para std::isinf e M_PI

using std::placeholders::_1;

class LidarListener : public rclcpp::Node {
public:
    LidarListener() : Node("lidar_listener") {
        // QoS 10: Mantém uma fila pequena para garantir dados recentes
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "scan", 10, std::bind(&LidarListener::topic_callback, this, _1));
    }

private:
    void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) const {
        // Cabeçalho para separar cada volta do motor
        RCLCPP_INFO(this->get_logger(), "--- INÍCIO DA VARREDURA ---");

        int contagem_obstaculos = 0;

        // Loop por TODOS os pontos do sensor
        for (size_t i = 0; i < msg->ranges.size(); i++) {
            float current_dist = msg->ranges[i];

            // Filtro: Só imprime se a distância for válida
            // 1. Maior que o mínimo do sensor (evita ruído perto do motor)
            // 2. Menor que o máximo do sensor
            // 3. Não é infinito (std::isinf) -> Infinito significa que não bateu em nada
            if (current_dist > msg->range_min && 
                current_dist < msg->range_max && 
                !std::isinf(current_dist)) {
                
                // Cálculo do ângulo
                float angle_rad = msg->angle_min + (i * msg->angle_increment);
                float angle_deg = angle_rad * (180.0 / M_PI); // Converte Radianos -> Graus

                // Imprime: Ângulo formatado com 2 casas e Distância com 3 casas
                RCLCPP_INFO(this->get_logger(), 
                    "Detecção -> Ângulo: %6.2f° | Distância: %.3fm", 
                    angle_deg, current_dist);
                
                contagem_obstaculos++;
            }
        }

        if (contagem_obstaculos == 0) {
            RCLCPP_INFO(this->get_logger(), "Nenhum obstáculo detectado nesta volta.");
        } else {
            RCLCPP_INFO(this->get_logger(), "Total de pontos detectados: %d", contagem_obstaculos);
        }
        
        RCLCPP_INFO(this->get_logger(), "-------------------------");
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarListener>());
    rclcpp::shutdown();
    return 0;
}