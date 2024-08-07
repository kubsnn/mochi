#pragma once
#ifndef __USER_DTO_HPP__
#define __USER_DTO_HPP__

#include <json.hpp>
#include <string>

namespace mochi::models {

    class UserDto {
    public:
        UserDto() = default;
        UserDto(const std::string& username, const std::string& password) 
            : username_(username), password_(password) { }

        std::string& username() { return username_; }
        std::string& password() { return password_; }

        const std::string& username() const { return username_; }
        const std::string& password() const { return password_; }

    private:
        std::string username_;
        std::string password_;
    };

}

namespace mochi::core::mapping {
    
    using json = jaszyk::json;
    
    template <>
    inline json to_json(const mochi::models::UserDto& user) {
        return {
            { "username", user.username() },
            { "password", user.password() }
        };
    }

    template <>
    inline mochi::models::UserDto from_json(const json& value) {
        return mochi::models::UserDto{
            value["username"].get<std::string>(),
            value["password"].get<std::string>()
        };
    }

}



#endif // !__USER_DTO_HPP__