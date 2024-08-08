#pragma once
#ifndef MOCHI_WEB_APP_BUILDER_HPP
#define MOCHI_WEB_APP_BUILDER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "../controller_base.hpp"
#include "../dependency_resolver.hpp"
#include "http_server.hpp"

namespace mochi {

    namespace asio = boost::asio;
    namespace beast = boost::beast;
    using tcp = asio::ip::tcp;

    class web_app_builder {
        using controller_factories = http_server::controller_factories;
    public:
        web_app_builder(asio::io_context& io_context, unsigned short port);

        http_server build();

        template <class TController>
        void add_controller();

        template <class TService>
        void add_singleton();

        template <class TService>
        void add_transient();

        template <class TService>
        void add_scoped();
        
    private:
        asio::io_context& io_context_;
        controller_factories controllers_;
        dependency_resolver injector_;
        unsigned short port_;
    };
} // !namespace mochi

#include "impl/web_app_builder_impl.hpp"

#endif // !MOCHI_WEB_APP_BUILDER_HPP