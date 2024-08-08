#pragma once
#ifndef MOCHI_HTTP_SERVER_HPP
#define MOCHI_HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/container/flat_map.hpp>
#include "../controller_factory_base.hpp"
#include "../dependency_resolver.hpp"
#include "impl/controller_factories.hpp"
#include <memory>

namespace mochi {

    namespace asio = boost::asio;
    namespace beast = boost::beast;
    using tcp = asio::ip::tcp;

    class http_server {
        friend class web_app_builder;
        friend class http_session;

        using controller_factories = http::impl::controller_factories;
    public:
        http_server(http_server&& other) noexcept;
        ~http_server();

        void run();

    private:
        http_server(asio::io_context& io_context, unsigned short port, controller_factories&& controllerFactories, dependency_resolver&& injector);
        void doAccept();

        asio::io_context& io_context_;
        tcp::acceptor acceptor_;
        tcp::socket socket_;
        controller_factories controllerFactories_;
        const dependency_resolver injector_;
    };
}

#endif // !MOCHI_HTTP_SERVER_HPP