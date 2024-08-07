#include "web_app_builder.hpp"
#include <core/Logger.hpp>

namespace mochi::core {

    web_app_builder::web_app_builder(asio::io_context& io_context, unsigned short port)
        : io_context_(io_context), port_(port)
    {
        logger.info() << "Building server..." << std::endl;
    }

    HttpServer web_app_builder::build()
    {
        HttpServer server(io_context_, port_, std::move(controllers_), std::move(injector_));
        
        return server;
    }

}