#include <src/CYdLidar.h>
#include <iostream>
#include <signal.h>
#include <chrono>
#include <thread>
#include <map>


using namespace std;
using namespace ydlidar;

bool stop_node = false;
void sigHandler(int sig) {
    stop_node = true;
}


// Automatically detect the LiDAR port
std::string detectLidarPort(){
    std::map<std::string , std::string> ports = lidarPortList();
    std::string port = "/dev/ydlidar";

    if (ports.empty()){
        cerr << "No ports detected . Using default port : " << port << endl;
        return port;
    }

    for (const auto & p : ports){
        port = p.second ;
    }

    cout << " Using port : " << port << endl;
    return port;
}


int main() {
    signal(SIGINT, sigHandler);

    CYdLidar laser;

    // Configuração básica
    string port = detectLidarPort();
    int baud = 512000;
    int type = TYPE_TRIANGLE;
    int devtype = YDLIDAR_TYPE_SERIAL;
    bool single = false;
    float freq = 10.0f;
    int sample_rate = 9;
    float min_r = 0.01f, max_r = 32.0f;
    float min_a = -180.0f, max_a = 180.0f;

    laser.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());
    laser.setlidaropt(LidarPropSerialBaudrate, &baud, sizeof(int));
    laser.setlidaropt(LidarPropLidarType, &type, sizeof(int));
    laser.setlidaropt(LidarPropDeviceType, &devtype, sizeof(int));
    laser.setlidaropt(LidarPropSingleChannel, &single, sizeof(bool));
    laser.setlidaropt(LidarPropScanFrequency, &freq, sizeof(float));
    laser.setlidaropt(LidarPropSampleRate, &sample_rate, sizeof(int));
    laser.setlidaropt(LidarPropMinRange, &min_r, sizeof(float));
    laser.setlidaropt(LidarPropMaxRange, &max_r, sizeof(float));
    laser.setlidaropt(LidarPropMinAngle, &min_a, sizeof(float));
    laser.setlidaropt(LidarPropMaxAngle, &max_a, sizeof(float));

    if (!laser.initialize()) {
        cerr << "Error initializing LiDAR." << endl;
        return -1;
    }

    if (!laser.turnOn()) {
        cerr << "Error turning on LiDAR." << endl;
        return -1;
    }

    cout << "LiDAR turned on. Reading data..." << endl;
    while (!stop_node) {
        LaserScan scan;
        if (laser.doProcessSimple(scan)) {
            cout << "Points received: " 
                 << scan.points.size()
                 << " | Freq: " << scan.scanFreq << " Hz" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "Shutting down..." << endl;
    laser.turnOff();
    laser.disconnecting();

    return 0;
}
