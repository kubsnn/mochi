#pragma once
#ifndef __USER_DTO_HPP__
#define __USER_DTO_HPP__

#include <json.hpp>
#include <string>
#include <utility>
#include "mochi/json_converter.hpp"

namespace mochi::models {

    class user_dto {
    public:
        inline user_dto() noexcept = default;
        inline user_dto(std::string username, std::string password) noexcept
            : username_(std::move(username)), password_(std::move(password)) { }

        [[nodiscard]] inline std::string& username() noexcept { return username_; }
        [[nodiscard]] inline std::string& password() noexcept { return password_; }

        [[nodiscard]] inline const std::string& username() const noexcept { return username_; }
        [[nodiscard]] inline const std::string& password() const noexcept { return password_; }

    private:
        std::string username_;
        std::string password_;
    };

}

namespace mochi::mapping {
    
    using json = jaszyk::json;
    
    template <>
    inline json to_json(const mochi::models::user_dto& user) {
        return {
            { "username", user.username() },
            { "password", user.password() }
        };
    }

    template <>
    inline mochi::models::user_dto from_json(const json& value) {
        return mochi::models::user_dto{
            value["username"].get<std::string>(),
            value["password"].get<std::string>()
        };
    }

}



#endif // !__USER_DTO_HPP__