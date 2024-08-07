#pragma once
#ifndef __ACCOUNT_CONTROLLER_HPP__
#define __ACCOUNT_CONTROLLER_HPP__

#include <core/controller_base.hpp>
#include <services/IDatabase.hpp>
#include <models/UserDto.hpp>
#include <boost/beast.hpp>

namespace mochi::controllers {

    using namespace services;
    using namespace models;

    namespace beast = boost::beast;
    namespace http = boost::beast::http;

    class AccountController : public core::controller_base {
    public:
        inline static std::string route = "/api/account";

        inline AccountController() {
            add_route(http::verb::get, "/login", [](const UserDto &user) -> std::string {
                return user.username();
            });

            add_route(http::verb::get, "/register", [](const std::string &body) -> std::string {
                return "register";
            });

            add_route(http::verb::get, "/info", []() -> UserDto {
                return UserDto("test", "test");
            });

            add_route(http::verb::get, "/logout", []() -> std::string {
                return "logout";
            });
        }
    };

}

#endif // !__ACCOUNT_CONTROLLER_HPP__