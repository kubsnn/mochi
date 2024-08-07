#pragma once
#ifndef __CONTROLLERFACTORY_HPP__
#define __CONTROLLERFACTORY_HPP__

#include <memory>
#include <core/IControllerFactory.hpp>
#include <core/dependency_resolver.hpp>

namespace mochi::core {

    template <class TController>
    class ControllerFactory : public IControllerFactory {
    public:
        inline ~ControllerFactory() override = default;

        inline std::unique_ptr<controller_base> create(const dependency_resolver& injector, dependency_resolver::scope& scope) override {
            return injector.resolve_unique<TController>(scope);
        }
    };

}
#endif // !__CONTROLLERFACTORY_HPP__