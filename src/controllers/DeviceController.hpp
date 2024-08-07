#pragma once
#ifndef __DEVICECONTROLLER_HPP__
#define __DEVICECONTROLLER_HPP__

#include <models/DeviceInfo.hpp>
#include <core/controller_base.hpp>
#include <boost/beast.hpp>
#include <string>
#include <string_view>
#include <services/DeviceService.hpp>
#include <memory>

namespace mochi::controllers {

    namespace http = boost::beast::http;
    using namespace mochi::services;
    using namespace mochi::models;

    class DeviceController : public core::controller_base {

        std::shared_ptr<DeviceService> deviceService_;
    public:
        inline static std::string_view route = "/api/device"; 

        inline explicit DeviceController(std::shared_ptr<DeviceService> deviceService)
            : deviceService_(std::move(deviceService))
        {
            add_route(http::verb::get, "/info", [this]() -> DeviceInfo {
                return getDeviceInfo();
            });
        }
    private:
        
        DeviceInfo getDeviceInfo();
    
    };

}


#endif // !__DEVICECONTROLLER_HPP__