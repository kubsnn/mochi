#pragma once
#ifndef MOCHI_CONTROLLER_FACTORY_HPP
#define MOCHI_CONTROLLER_FACTORY_HPP

#include "controller_factory_base.hpp"
#include "dependency_resolver.hpp"
#include <memory>

namespace mochi {

    template <class TController>
    class controller_factory : public controller_factory_base {
    public:
        inline ~controller_factory() override = default;

        inline std::unique_ptr<controller_base> create(const dependency_resolver& injector, dependency_resolver::scope& scope) override {
            return injector.resolve_unique<TController>(scope);
        }
    };

} // !mochi
#endif // !MOCHI_CONTROLLER_FACTORY_HPP