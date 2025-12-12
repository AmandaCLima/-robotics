#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_broadcaster.h>
#include <dynamic_reconfigure/server.h>
#include <ydlidar_ros_driver/ydlidarConfig.h>
#include <src/CYdLidar.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <map>
#include <string>

using namespace std;
using namespace ydlidar;

class YDLidarNode {
private:
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;
    ros::Publisher scan_pub_;
    tf::TransformBroadcaster tf_broadcaster_;
    
    dynamic_reconfigure::Server<ydlidar_ros_driver::ydlidarConfig> server_;
    dynamic_reconfigure::Server<ydlidar_ros_driver::ydlidarConfig>::CallbackType f_;
    
    CYdLidar laser_;
    bool stop_node_;
    std::string frame_id_;
    
public:
    YDLidarNode() : 
        private_nh_("~"),
        stop_node_(false) {
        
        // Inicialização
        scan_pub_ = nh_.advertise<sensor_msgs::LaserScan>("scan", 100);
        
        // Configuração do dynamic_reconfigure
        f_ = boost::bind(&YDLidarNode::configCallback, this, _1, _2);
        server_.setCallback(f_);
        
        // Parâmetros
        private_nh_.param<std::string>("frame_id", frame_id_, "laser_frame");
        
        // Signal handler
        signal(SIGINT, &YDLidarNode::sigHandler);
        
        setupLidar();
    }
    
    static void sigHandler(int sig) {
        ROS_INFO("Received signal %d, shutting down...", sig);
        ros::shutdown();
    }
    
    void configCallback(ydlidar_ros_driver::ydlidarConfig &config, uint32_t level) {
        ROS_INFO("Reconfigure request received");
        
        // Reconfigura o LiDAR
        laser_.setlidaropt(LidarPropSerialPort, config.port.c_str(), config.port.size());
        laser_.setlidaropt(LidarPropSerialBaudrate, &config.baudrate, sizeof(int));
        laser_.setlidaropt(LidarPropScanFrequency, &config.scan_frequency, sizeof(float));
        laser_.setlidaropt(LidarPropSampleRate, &config.sample_rate, sizeof(int));
        laser_.setlidaropt(LidarPropMinRange, &config.min_range, sizeof(float));
        laser_.setlidaropt(LidarPropMaxRange, &config.max_range, sizeof(float));
        laser_.setlidaropt(LidarPropMinAngle, &config.min_angle, sizeof(float));
        laser_.setlidaropt(LidarPropMaxAngle, &config.max_angle, sizeof(float));
        laser_.setlidaropt(LidarPropSingleChannel, &config.single_channel, sizeof(bool));
        laser_.setlidaropt(LidarPropInverted, &config.invert, sizeof(bool));
        
        if (laser_.isScanning()) {
            laser_.turnOff();
            ros::Duration(0.5).sleep();
            if (!laser_.turnOn()) {
                ROS_ERROR("Failed to restart LiDAR with new configuration");
            }
        }
    }
    
    std::string detectLidarPort() {
        std::map<std::string, std::string> ports = lidarPortList();
        std::string port = "/dev/ydlidar";
        
        if (ports.empty()) {
            ROS_WARN("No LiDAR ports detected. Using default: %s", port.c_str());
            return port;
        }
        
        for (const auto &p : ports) {
            port = p.second;
            ROS_INFO("Found LiDAR on port: %s", port.c_str());
            break;
        }
        
        return port;
    }
    
    void setupLidar() {
        // Parâmetros padrão
        std::string port;
        int baudrate = 512000;
        float scan_frequency = 10.0;
        int sample_rate = 9;
        float min_range = 0.01;
        float max_range = 32.0;
        float min_angle = -180.0;
        float max_angle = 180.0;
        bool single_channel = false;
        bool invert = false;
        
        private_nh_.param<std::string>("port", port, detectLidarPort());
        private_nh_.param<int>("baudrate", baudrate, baudrate);
        private_nh_.param<float>("scan_frequency", scan_frequency, scan_frequency);
        private_nh_.param<int>("sample_rate", sample_rate, sample_rate);
        private_nh_.param<float>("min_range", min_range, min_range);
        private_nh_.param<float>("max_range", max_range, max_range);
        private_nh_.param<float>("min_angle", min_angle, min_angle);
        private_nh_.param<float>("max_angle", max_angle, max_angle);
        private_nh_.param<bool>("single_channel", single_channel, single_channel);
        private_nh_.param<bool>("invert", invert, invert);
        
        // Configuração do LiDAR
        laser_.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());
        laser_.setlidaropt(LidarPropSerialBaudrate, &baudrate, sizeof(int));
        laser_.setlidaropt(LidarPropScanFrequency, &scan_frequency, sizeof(float));
        laser_.setlidaropt(LidarPropSampleRate, &sample_rate, sizeof(int));
        laser_.setlidaropt(LidarPropMinRange, &min_range, sizeof(float));
        laser_.setlidaropt(LidarPropMaxRange, &max_range, sizeof(float));
        laser_.setlidaropt(LidarPropMinAngle, &min_angle, sizeof(float));
        laser_.setlidaropt(LidarPropMaxAngle, &max_angle, sizeof(float));
        laser_.setlidaropt(LidarPropSingleChannel, &single_channel, sizeof(bool));
        laser_.setlidaropt(LidarPropInverted, &invert, sizeof(bool));
        
        int type = TYPE_TRIANGLE;
        int devtype = YDLIDAR_TYPE_SERIAL;
        laser_.setlidaropt(LidarPropLidarType, &type, sizeof(int));
        laser_.setlidaropt(LidarPropDeviceType, &devtype, sizeof(int));
        
        // Inicialização
        if (!laser_.initialize()) {
            ROS_FATAL("Failed to initialize LiDAR on port %s", port.c_str());
            ros::shutdown();
        }
        
        if (!laser_.turnOn()) {
            ROS_FATAL("Failed to turn on LiDAR");
            ros::shutdown();
        }
        
        ROS_INFO("YDLidar initialized successfully on port %s", port.c_str());
    }
    
    sensor_msgs::LaserScan toRosScan(const LaserScan &scan) {
        sensor_msgs::LaserScan scan_msg;
        
        scan_msg.header.stamp = ros::Time::now();
        scan_msg.header.frame_id = frame_id_;
        
        scan_msg.angle_min = scan.config.min_angle * M_PI / 180.0;
        scan_msg.angle_max = scan.config.max_angle * M_PI / 180.0;
        scan_msg.angle_increment = scan.config.angle_increment * M_PI / 180.0;
        
        scan_msg.time_increment = scan.config.time_increment;
        scan_msg.scan_time = scan.config.scan_time;
        
        scan_msg.range_min = scan.config.min_range;
        scan_msg.range_max = scan.config.max_range;
        
        scan_msg.ranges.resize(scan.points.size());
        scan_msg.intensities.resize(scan.points.size());
        
        for (size_t i = 0; i < scan.points.size(); i++) {
            scan_msg.ranges[i] = scan.points[i].range;
            scan_msg.intensities[i] = scan.points[i].intensity;
        }
        
        return scan_msg;
    }
    
    void publishTf() {
        tf::Transform transform;
        transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
        tf::Quaternion q;
        q.setRPY(0, 0, 0);
        transform.setRotation(q);
        
        tf_broadcaster_.sendTransform(
            tf::StampedTransform(transform, ros::Time::now(), 
                               "base_link", frame_id_));
    }
    
    void run() {
        ros::Rate rate(20);
        
        while (ros::ok() && !stop_node_) {
            LaserScan scan;
            
            if (laser_.doProcessSimple(scan)) {
                sensor_msgs::LaserScan scan_msg = toRosScan(scan);
                scan_pub_.publish(scan_msg);
                
                // Publica TF
                publishTf();
                
                // Log para debug (1Hz)
                static ros::Time last_log = ros::Time::now();
                if ((ros::Time::now() - last_log).toSec() > 1.0) {
                    ROS_DEBUG("Scan: %zu points, %.2f Hz", 
                             scan.points.size(), scan.scanFreq);
                    last_log = ros::Time::now();
                }
            }
            
            ros::spinOnce();
            rate.sleep();
        }
        
        shutdown();
    }
    
    void shutdown() {
        ROS_INFO("Shutting down YDLidar node...");
        laser_.turnOff();
        laser_.disconnecting();
    }
    
    ~YDLidarNode() {
        shutdown();
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "ydlidar_node");
    
    try {
        YDLidarNode node;
        node.run();
    } catch (const std::exception& e) {
        ROS_FATAL("Exception in YDLidar node: %s", e.what());
        return 1;
    }
    
    return 0;
}