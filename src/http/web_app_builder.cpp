#include "web_app_builder.hpp"
#include "../logger.hpp"

namespace mochi {

    web_app_builder::web_app_builder(asio::io_context& io_context, unsigned short port)
        : io_context_(io_context), port_(port)
    {
        log.info() << "Building server..." << std::endl;
    }

    http_server web_app_builder::build()
    {
        http_server server(io_context_, port_, std::move(controllers_), std::move(injector_));
        
        return server;
    }

} // namespace mochi