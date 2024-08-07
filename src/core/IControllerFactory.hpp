#pragma once
#ifndef APP_CORE_ICONTROLLER_FACTORY_HPP
#define APP_CORE_ICONTROLLER_FACTORY_HPP

#include <memory>
#include <core/controller_base.hpp>
#include <core/dependency_resolver.hpp>

namespace mochi::core {

    class IControllerFactory {
    public:
        virtual ~IControllerFactory() = default;

        virtual std::unique_ptr<controller_base> create(const dependency_resolver&, dependency_resolver::scope&) = 0;
    };

} // namespace app::core

#endif // !APP_CORE_ICONTROLLER_FACTORY_HPP