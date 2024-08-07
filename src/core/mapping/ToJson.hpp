#pragma once 
#ifndef __APP_CORE_MAPPING_TO_JSON_HPP__
#define __APP_CORE_MAPPING_TO_JSON_HPP__

#include <json.hpp>
#include <core/utility/Traits.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace mochi::core::mapping {

    using json = jaszyk::json;

    template <typename T>
    inline json to_json(const T&) {
        static_assert(utility::AlwaysFalse<T>::value, "to_json not implemented for this type");
        return json::null{};
    }

    template <>
    inline json to_json(const std::string& value) {
        return {value};
    }

    template <>
    inline json to_json(const std::string_view& value) {
        return {std::string(value)};
    }

    template <>
    inline json to_json(const short& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const int& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const unsigned int& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const long& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const long long& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const float& value) {
        return {(double)value};
    }

    template <>
    inline json to_json(const double& value) {
        return {value};
    }

    template <>
    inline json to_json(const bool& value) {
        return {value};
    }

    template <typename T>
    inline json to_json(const std::vector<T>& value) {
        json::array result;

        for (const auto& item : value) {
            result.push_back(to_json(item));
        }

        return result;
    }

} // namespace app::core::mapping

#endif // !__JSON_MAPPER_HPP__