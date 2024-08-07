#pragma once
#ifndef CORE_HTTPSERVER_HPP
#define CORE_HTTPSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/container/flat_map.hpp>
#include <core/IControllerFactory.hpp>
#include <core/dependency_resolver.hpp>
#include <core/http/impl/controller_factories.hpp>
#include <memory>

namespace mochi::core {

    namespace asio = boost::asio;
    namespace beast = boost::beast;
    using tcp = asio::ip::tcp;

    class HttpServer {
        friend class web_app_builder;
        friend class HttpSession;

        using controller_factories = http::impl::controller_factories;
    public:
        HttpServer(HttpServer&& other) noexcept;
        ~HttpServer();

        void run();

    private:
        HttpServer(asio::io_context& io_context, unsigned short port, controller_factories&& controllerFactories, dependency_resolver&& injector);
        void doAccept();

        asio::io_context& io_context_;
        tcp::acceptor acceptor_;
        tcp::socket socket_;
        controller_factories controllerFactories_;
        const dependency_resolver injector_;
    };
}

#endif // !CORE_HTTPSERVER_HPP