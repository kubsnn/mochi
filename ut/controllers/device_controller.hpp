#pragma once
#ifndef MOCHI_CONTROLLERS_DEVICE_CONTROLLER_HPP
#define MOCHI_CONTROLLERS_DEVICE_CONTROLLER_HPP

#include <boost/beast.hpp>
#include "../models/device_info.hpp"
#include "mochi/controller_base.hpp"
#include "../services/device_service.hpp"
#include <string>
#include <string_view>
#include <memory>

namespace mochi::controllers {

    namespace http = boost::beast::http;
    using namespace mochi::services;
    using namespace mochi::models;

    class device_controller : public controller_base {

        std::shared_ptr<device_service> deviceService_;
    public:
        inline static std::string_view route = "/api/device"; 

        inline explicit device_controller(std::shared_ptr<device_service> deviceService)
            : deviceService_(std::move(deviceService))
        {
            add_route(http::verb::get, "/info", [this]() -> device_info {
                return getDeviceInfo();
            });
        }
    private:
        
        device_info getDeviceInfo();
    
    };

}


#endif // !MOCHI_CONTROLLERS_DEVICE_CONTROLLER_HPP