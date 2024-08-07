#include "DeviceService.hpp"
#include <core/Logger.hpp>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>

namespace mochi::services {
    
    DeviceInfo DeviceService::getDeviceInfo() const
    {
        return DeviceInfo{"Raspberry Pi 5",  getIpAddress(), getTemperature()};
    }

    float DeviceService::getTemperature() const
    {
        std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
        if (!file.is_open()) {
            mochi::core::logger.error() << "Cannot open file with temperature." << std::endl;
            return 0.0f;
        }

        std::string line;
        std::getline(file, line);
        file.close();

        return std::stoi(line) / 1000.0f;
    }

    std::string DeviceService::getIpAddress() const
    {
        std::ifstream file("/proc/net/route");
        if (!file.is_open()) {
            mochi::core::logger.error() << "Cannot open file with ip address." << std::endl;
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