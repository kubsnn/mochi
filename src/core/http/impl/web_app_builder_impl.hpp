#pragma once
#ifndef MOCHI_CORE_HTTP_WEB_APP_BUILDER_IMPL_HPP
#define MOCHI_CORE_HTTP_WEB_APP_BUILDER_IMPL_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <core/ControllerFactory.hpp>

namespace mochi::core {

    namespace asio = boost::asio;
    namespace beast = boost::beast;

    class web_app_builder;

    template <class TController>
    inline void web_app_builder::add_controller()
    {
        controllers_.emplace(TController::route, std::make_unique<ControllerFactory<TController>>());
    }

    template <class TService>
    inline void web_app_builder::add_singleton()
    {
        injector_.add_singleton<TService>();
    }

    template <class TService>
    inline void web_app_builder::add_transient()
    {
        injector_.add_transient<TService>();
    }

    template <class TService>
    inline void web_app_builder::add_scoped()
    {
        injector_.add_scoped<TService>();
    }

} // namespace app::core

#endif // !MOCHI_CORE_HTTP_WEB_APP_BUILDER_IMPL_HPP

