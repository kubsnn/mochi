#pragma once
#ifndef APP_CORE_WEB_APP_BUILDER_HPP
#define APP_CORE_WEB_APP_BUILDER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <core/controller_base.hpp>
#include <core/dependency_resolver.hpp>
#include <core/http/HttpServer.hpp>
#include <core/utility/ExtensibleTuple.hpp>

namespace mochi::core {

    namespace asio = boost::asio;
    namespace beast = boost::beast;
    using tcp = asio::ip::tcp;

    class web_app_builder {
        using controller_factories = HttpServer::controller_factories;
    public:
        web_app_builder(asio::io_context& io_context, unsigned short port);

        HttpServer build();

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
}

#include <core/http/impl/web_app_builder_impl.hpp>

#endif // !APP_CORE_WEB_APP_BUILDER_HPP