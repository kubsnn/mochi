#pragma once 
#ifndef MOCHI_MAPPING_FROM_JSON_HPP
#define MOCHI_MAPPING_FROM_JSON_HPP

#include "json.hpp"
#include "../utility/traits.hpp"
#include <vector>
#include <string>
#include <string_view>

namespace mochi::mapping {

    using json = jaszyk::json;

    template <typename T>
    inline T from_json(const json&) {
        static_assert(utility::AlwaysFalse<T>::value, "from_json not implemented for this type");
        return T{};
    }

    template <>
    inline std::string from_json(const json& value) {
        return value.get<std::string>();
    }

    template <>
    inline std::string_view from_json(const json& value) {
        return value.get<std::string>();
    }

    template <>
    inline int from_json(const json& value) {
        return value.get<double>();
    }

    template <>
    inline long from_json(const json& value) {
        return value.get<double>();
    }

    template <>
    inline long long from_json(const json& value) {
        return value.get<double>();
    }

    template <>
    inline float from_json(const json& value) {
        return value.get<double>();
    }

    template <>
    inline double from_json(const json& value) {
        return value.get<double>();
    }

    template <>
    inline bool from_json(const json& value) {
        return value.get<bool>();
    }

    // template <typename T>
    // inline std::vector<T> from_json(const json& value) {
    //     std::vector<T> result;
    //     result.reserve(value.get<json::array>().size());

    //     for (const auto& item : value.get<json::array>()) {
    //         result.push_back(from_json<T>(item));
    //     }

    //     return result;
    // }


} // namespace app::mapping

#endif // !MOCHI_MAPPING_FROM_JSON_HPP