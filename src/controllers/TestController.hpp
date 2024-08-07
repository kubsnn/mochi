#pragma once
#ifndef __TESTCONTROLLER_HPP__
#define __TESTCONTROLLER_HPP__

#include <string>
#include <core/controller_base.hpp>
#include <string_view>
#include <services/IDatabase.hpp>
#include <services/Database.hpp>
#include <models/UserDto.hpp>
#include <boost/beast.hpp>

namespace mochi::controllers {

    using namespace services;
    namespace beast = boost::beast;

    class TestController : public core::controller_base {
    public:
        inline static std::string route = "/api/test";

        inline TestController(std::shared_ptr<Database> database, std::shared_ptr<TestService> testService) { 
            database->connect();

            add_route(beast::http::verb::get, "/test", [](std::string body) {
                return models::UserDto("test", "test");
            });

            add_route(beast::http::verb::get, "/test2", [](models::UserDto &user) -> std::string {
                return user.username() + " " + user.password();
            });
        }
    };

}

#endif // !__TESTCONTROLLER_HPP__