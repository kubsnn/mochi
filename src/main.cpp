#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <models/DeviceInfo.hpp>
#include <models/UserDto.hpp>

#include <core/http/web_app_builder.hpp>

#include <controllers/DeviceController.hpp>
#include <controllers/AccountController.hpp>
#include <services/DeviceService.hpp>
 

using namespace mochi::core;
using namespace mochi::controllers;
using namespace mochi::services;

#include <json.hpp>

using json = jaszyk::json;

int main() {
    std::ios_base::sync_with_stdio(false);

    asio::io_context context{ (int)std::thread::hardware_concurrency() };
    web_app_builder builder(context, 8080);

    builder.add_controller<DeviceController>();
    builder.add_controller<AccountController>();

    builder.add_scoped<DeviceService>();

    auto app = builder.build();
    
    app.run();
}
