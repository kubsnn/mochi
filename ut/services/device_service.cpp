#include "device_service.hpp"
#include "mochi/logger.hpp"
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>

namespace mochi::services {
    
    device_info device_service::getDeviceInfo() const
    {
        return device_info{"Raspberry Pi 5", getIpAddress(), getTemperature()};
    }

    float device_service::getTemperature() const
    {
        std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
        if (!file.is_open()) {
            mochi::log.error() << "Cannot open file with temperature." << std::endl;
            return 0.0f;
        }

        std::string line;
        std::getline(file, line);
        file.close();

        return std::stoi(line) / 1000.0f;
    }

    std::string device_service::getIpAddress() const
    {
        std::ifstream file("/proc/net/route");
        if (!file.is_open()) {
            mochi::log.error() << "Cannot open file with ip address." << std::endl;
            return "";
        }

        std::string line;
        std::getline(file, line);
        file.close();

        std::string ip;
        std::string iface;
        std::istringstream iss(line);
        iss >> iface >> ip;

        return ip;
    }
}