#pragma once
#ifndef __DEVICEINFO_HPP__
#define __DEVICEINFO_HPP__

#include <string>
#include <string_view>
#include <json.hpp>
#include <core/mapping/ToJson.hpp>
#include <core/mapping/FromJson.hpp>


namespace mochi::models {

    using json = jaszyk::json;

    class DeviceInfo {
    public:
        DeviceInfo() = default;
        DeviceInfo(const std::string& name, const std::string& ip, const float& temperature)
            : name_(name), ip_(ip), temperature_(temperature) 
        { }

        std::string& name() { return name_; }
        std::string& ip() { return ip_; }
        float& temperature() { return temperature_; }

        const std::string& name() const { return name_; }
        const std::string& ip() const { return ip_; }
        const float& temperature() const { return temperature_; }

    private:
        std::string name_;
        std::string ip_;
        float temperature_;
    };
}

namespace mochi::core::mapping {

    using json = jaszyk::json;

    template <>
    inline json to_json(const mochi::models::DeviceInfo& device) {
        return {
            { "name", device.name() },
            { "ip", device.ip() },
            { "temperature", (double)device.temperature() }
        };
    }

    template <>
    inline mochi::models::DeviceInfo from_json(const json& value) {
        return mochi::models::DeviceInfo{
            value["name"].get<std::string>(),
            value["ip"].get<std::string>(),
            (float)value["temperature"].get<double>()
        };
    }

} 

#endif // !__DEVICEINFO_HPP__