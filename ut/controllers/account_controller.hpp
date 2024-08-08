#pragma once
#ifndef MOCHI_CONTROLLERS_ACCOUNT_CONTROLLER_HPP
#define MOCHI_CONTROLLERS_ACCOUNT_CONTROLLER_HPP

#include <boost/beast.hpp>
#include "mochi/controller_base.hpp"
#include "../services/database_base.hpp"
#include "../models/user_dto.hpp"

namespace mochi::controllers {

    using namespace services;
    using namespace models;

    namespace beast = boost::beast;
    namespace http = boost::beast::http;

    class account_controller : public controller_base {
    public:
        inline static std::string route = "/api/account";

        inline account_controller() {
            add_route(http::verb::get, "/login", [](const user_dto &user) -> std::string {
                return user.username();
            });

            add_route(http::verb::get, "/register", [](const std::string &body) -> std::string {
                return "register";
            });

            add_route(http::verb::get, "/info", []() -> user_dto {
                return user_dto("test", "test");
            });

            add_route(http::verb::get, "/logout", []() -> std::string {
                return "logout";
            });
        }
    };

}

#endif // !MOCHI_CONTROLLERS_ACCOUNT_CONTROLLER_HPP