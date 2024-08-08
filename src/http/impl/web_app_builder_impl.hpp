#pragma once
#ifndef MOCHI_HTTP_WEB_APP_BUILDER_IMPL_HPP
#define MOCHI_HTTP_WEB_APP_BUILDER_IMPL_HPP

#include "../../controller_factory.hpp"

namespace mochi {

    class web_app_builder;

    template <class TController>
    inline void web_app_builder::add_controller()
    {
        controllers_.emplace(TController::route, std::make_unique<controller_factory<TController>>());
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

} // namespace app

#endif // !MOCHI_HTTP_WEB_APP_BUILDER_IMPL_HPP

