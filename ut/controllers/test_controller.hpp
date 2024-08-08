#pragma once
#ifndef MOCHI_CONTROLLERS_TEST_CONTROLLER_HPP
#define MOCHI_CONTROLLERS_TEST_CONTROLLER_HPP

#include <boost/beast.hpp>
#include "mochi/controller_base.hpp"
#include "../services/database_base.hpp"
#include "../services/database.hpp"
#include "../models/user_dto.hpp"
#include "mochi/json_converter.hpp"
#include <string_view>
#include <string>

namespace mochi::controllers {

    using namespace services;
    namespace beast = boost::beast;

    class test_controller : public controller_base {
    public:
        inline static std::string route = "/api/test";

        inline test_controller(std::shared_ptr<database> database, std::shared_ptr<test_service> testService) {
            database->connect();

            add_route(beast::http::verb::get, "/test", [](std::string body) {
                return models::user_dto("test", "test");
            });

            add_route(beast::http::verb::get, "/test2", [](models::user_dto &user) -> std::string {
                return user.username() + " " + user.password();
            });
        }
    };

}

#endif // !MOCHI_CONTROLLERS_TEST_CONTROLLER_HPP