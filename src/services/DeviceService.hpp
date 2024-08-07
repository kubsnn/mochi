#pragma once
#ifndef __DEVICESERVICE_HPP__
#define __DEVICESERVICE_HPP__

#include <models/DeviceInfo.hpp>   

namespace mochi::services {

    using namespace mochi::models;
    
    class DeviceService {
    public:
        DeviceService() = default;

        DeviceInfo getDeviceInfo() const;
    
    private:
        float getTemperature() const;
        std::string getIpAddress() const;
    };
}

#endif // !__DEVICESERVICE_HPP__