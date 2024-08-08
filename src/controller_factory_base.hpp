#pragma once
#ifndef MOCHI_CONTROLLER_FACTORY_BASE_HPP
#define MOCHI_CONTROLLER_FACTORY_BASE_HPP

#include "controller_base.hpp"
#include "dependency_resolver.hpp"
#include <memory>

namespace mochi {

    class controller_factory_base {
    public:
        virtual ~controller_factory_base() = default;

        virtual std::unique_ptr<controller_base> create(const dependency_resolver&, dependency_resolver::scope&) = 0;
    };

} // namespace app

#endif // !MOCHI_CONTROLLER_FACTORY_BASE_HPP