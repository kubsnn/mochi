    #include "HttpServer.hpp"
#include <core/http/HttpSession.hpp>
#include <core/IControllerFactory.hpp>
#include <core/Logger.hpp>
#include <iostream>
#include <memory>
#include <thread>

namespace mochi::core {

    HttpServer::HttpServer(asio::io_context& io_context, unsigned short port, controller_factories&& controllerFactories, dependency_resolver&& injector)
        : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
        , socket_(io_context), controllerFactories_(std::move(controllerFactories)), injector_(std::move(injector))
    {
        logger.info() << "Binding OK." << std::endl;
        logger.info() << "Listening on 0.0.0.0:" << port << '.' << std::endl;
        doAccept();
    }

    HttpServer::HttpServer(HttpServer&& other) noexcept
        : io_context_(other.io_context_), acceptor_(std::move(other.acceptor_))
        , socket_(std::move(other.socket_)), controllerFactories_(std::move(other.controllerFactories_))
    {
    }

    HttpServer::~HttpServer() = default;

    void HttpServer::run()
    {
        auto threads = std::thread::hardware_concurrency();
        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for(auto i = threads - 1; i > 0; --i) {
            v.emplace_back([this] {
                io_context_.run();
            });
        }

        logger.info() << "Application started." << std::endl;
        io_context_.run();
    }

    void HttpServer::doAccept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                // Create a new HttpSession and run it
                std::make_shared<HttpSession>(std::move(socket_), controllerFactories_, injector_)->run();
            } else {
                logger.error() << "Error in accepting connection: " << ec.message() << std::endl;
            }

            // Continue accepting connections
            doAccept();
        });
    }

    
}