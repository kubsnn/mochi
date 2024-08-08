#pragma once
#ifndef __DEVICEINFO_HPP__
#define __DEVICEINFO_HPP__

#include <string>
#include <string_view>
#include <json.hpp>
#include "mochi/json_converter.hpp"
#include <utility>


namespace mochi::models {

    using json = jaszyk::json;

    class device_info {
    public:
        inline device_info() = default;
        inline device_info(std::string  name, std::string  ip, const float& temperature)
            : name_(std::move(name)), ip_(std::move(ip)), temperature_(temperature)
        { }

        [[nodiscard]] inline std::string& name() { return name_; }
        [[nodiscard]] inline std::string& ip() { return ip_; }
        [[nodiscard]] inline float& temperature() { return temperature_; }

        [[nodiscard]] inline const std::string& name() const { return name_; }
        [[nodiscard]] inline const std::string& ip() const { return ip_; }
        [[nodiscard]] inline const float& temperature() const { return temperature_; }

    private:
        std::string name_;
        std::string ip_;
        float temperature_ = 0;
    };
}

namespace mochi::mapping {

    using json = jaszyk::json;

    template <>
    inline json to_json(const mochi::models::device_info& device) {
        return {
            { "name", device.name() },
            { "ip", device.ip() },
            { "temperature", (double)device.temperature() }
        };
    }

    template <>
    inline mochi::models::device_info from_json(const json& value) {
        return mochi::models::device_info{
            value["name"].get<std::string>(),
            value["ip"].get<std::string>(),
            (float)value["temperature"].get<double>()
        };
    }

} 

#endif // !__DEVICEINFO_HPP__