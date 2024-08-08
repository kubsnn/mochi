#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <mochi/http_server.hpp>
#include <mochi/controller_base.hpp>

#include "controllers/device_controller.hpp"
#include "controllers/account_controller.hpp"
#include "services/device_service.hpp"
 

using namespace mochi;
using namespace mochi::controllers;
using namespace mochi::services;

#include "json.hpp"

using json = jaszyk::json;

int main() {
    std::ios_base::sync_with_stdio(false);

    asio::io_context context{ (int)std::thread::hardware_concurrency() };
    web_app_builder builder(context, 8080);

    builder.add_controller<device_controller>();
    builder.add_controller<account_controller>();

    builder.add_scoped<device_service>();

    auto app = builder.build();

    app.run();
}
