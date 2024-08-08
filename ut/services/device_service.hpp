#pragma once
#ifndef MOCHI_CONTROLLERS_DEVICESERVICE_HPP
#define MOCHI_CONTROLLERS_DEVICESERVICE_HPP

#include "../models/device_info.hpp"

namespace mochi::services {

    using namespace mochi::models;
    
    class device_service {
    public:
        device_service() = default;

        device_info getDeviceInfo() const;
    
    private:
        float getTemperature() const;
        std::string getIpAddress() const;
    };
}

#endif // !MOCHI_CONTROLLERS_DEVICESERVICE_HPP