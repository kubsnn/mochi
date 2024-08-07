#pragma once
#ifndef __APP_CORE_HTTP_IMPL_CONTROLLERFACTORY_HPP__
#define __APP_CORE_HTTP_IMPL_CONTROLLERFACTORY_HPP__

#include <boost/container/flat_map.hpp>
#include <core/IControllerFactory.hpp>
#include <string>
#include <memory>

namespace mochi::core::http::impl {

    struct controller_comparer {
        inline bool operator()(const std::string& lhs, const std::string& rhs) const {
            return lhs.length() > rhs.length();
        }
    };

    using controller_factories =
        boost::container::flat_map<std::string, std::unique_ptr<IControllerFactory>, controller_comparer>;
    
}

#endif // !__APP_CORE_HTTP_IMPL_CONTROLLERFACTORY_HPP__