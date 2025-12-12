#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <CYdLidar.h> // Ou <ydlidar_sdk/CYdLidar.h> dependendo da instalação
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include <cmath> // Para conversão Graus -> Radianos

using namespace std;
using namespace ydlidar;

class YDLidarPublisher : public rclcpp::Node {
public:
    YDLidarPublisher() : Node("ydlidar_publisher") {
        // 1. Cria o Publisher no tópico "/scan"
        publisher_ = this->create_publisher<sensor_msgs::msg::LaserScan>("scan", 10);

        // 2. Configura e inicia o Hardware
        if (!initLidar()) {
            RCLCPP_ERROR(this->get_logger(), "Falha ao iniciar o LiDAR! Encerrando nó...");
            rclcpp::shutdown();
            return;
        }

        // 3. Timer para ler os dados ciclicamente (10Hz = 100ms)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&YDLidarPublisher::timerCallback, this)
        );
    }

    // Destrutor: Desliga o laser corretamente ao fechar o nó
    ~YDLidarPublisher() {
        RCLCPP_INFO(this->get_logger(), "Desligando LiDAR...");
        laser_.turnOff();
        laser_.disconnecting();
    }

private:
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    CYdLidar laser_;
    string frame_id_ = "laser_frame";

    // Sua função original de detecção de porta (adaptada para a classe)
    std::string detectLidarPort() {
        std::map<std::string, std::string> ports = lidarPortList();
        std::string port = "/dev/ydlidar";

        if (ports.empty()) {
            RCLCPP_WARN(this->get_logger(), "Nenhuma porta detectada. Usando padrão: %s", port.c_str());
            return port;
        }

        for (const auto &p : ports) {
            port = p.second;
        }
        
        RCLCPP_INFO(this->get_logger(), "Porta detectada: %s", port.c_str());
        return port;
    }

    bool initLidar() {
        string port = detectLidarPort();
        
        // Parâmetros do seu código original
        int baud = 512000; // <--- Verifique se seu modelo suporta isso (X4/G4 geralmente suportam)
        int type = TYPE_TRIANGLE;
        int devtype = YDLIDAR_TYPE_SERIAL;
        bool single = false;
        float freq = 6.0f;
        int sample_rate = 9;
        float min_r = 0.01f, max_r = 32.0f;
        float min_a = -180.0f, max_a = 180.0f;

        // Setando opções
        laser_.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());
        laser_.setlidaropt(LidarPropSerialBaudrate, &baud, sizeof(int));
        laser_.setlidaropt(LidarPropLidarType, &type, sizeof(int));
        laser_.setlidaropt(LidarPropDeviceType, &devtype, sizeof(int));
        laser_.setlidaropt(LidarPropSingleChannel, &single, sizeof(bool));
        laser_.setlidaropt(LidarPropScanFrequency, &freq, sizeof(float));
        laser_.setlidaropt(LidarPropSampleRate, &sample_rate, sizeof(int));
        laser_.setlidaropt(LidarPropMinRange, &min_r, sizeof(float));
        laser_.setlidaropt(LidarPropMaxRange, &max_r, sizeof(float));
        laser_.setlidaropt(LidarPropMinAngle, &min_a, sizeof(float));
        laser_.setlidaropt(LidarPropMaxAngle, &max_a, sizeof(float));

        if (!laser_.initialize()) return false;
        if (!laser_.turnOn()) return false;

        return true;
    }

    void timerCallback() {
        LaserScan scan;
        
        // Tenta ler do hardware
        if (laser_.doProcessSimple(scan)) {
            auto msg = convertToRosMsg(scan);
            publisher_->publish(msg);
            
            // Log simples para debug (opcional)
            // RCLCPP_INFO(this->get_logger(), "Publicado scan com %lu pontos", scan.points.size());
        }
    }

    sensor_msgs::msg::LaserScan convertToRosMsg(const LaserScan& src) {
        sensor_msgs::msg::LaserScan msg;
        
        // Cabeçalho da mensagem (Timestamp atual e Frame ID)
        msg.header.stamp = this->now();
        msg.header.frame_id = frame_id_;

        // Configurações angulares (Convertendo GRAUS para RADIANOS)
        // M_PI / 180.0 = 0.017453...
        msg.angle_min = src.config.min_angle * M_PI / 180.0;
        msg.angle_max = src.config.max_angle * M_PI / 180.0;
        msg.angle_increment = src.config.angle_increment * M_PI / 180.0;

        // Configurações de tempo e distância
        msg.scan_time = src.config.scan_time;
        msg.time_increment = src.config.time_increment;
        msg.range_min = src.config.min_range;
        msg.range_max = src.config.max_range;

        // Preenchendo os vetores de dados
        msg.ranges.resize(src.points.size());
        msg.intensities.resize(src.points.size());

        for (size_t i = 0; i < src.points.size(); i++) {
            float range = src.points[i].range;
            
            // Filtragem básica: se range for 0, coloca como infinito (padrão ROS)
            if (range == 0.0) {
                msg.ranges[i] = std::numeric_limits<float>::infinity();
            } else {
                msg.ranges[i] = range;
            }
            
            msg.intensities[i] = src.points[i].intensity;
        }

        return msg;
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<YDLidarPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}