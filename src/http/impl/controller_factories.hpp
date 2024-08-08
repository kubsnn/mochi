#pragma once
#ifndef MOCHI_HTTP_IMPL_CONTROLLER_FACTORY_HPP
#define MOCHI_HTTP_IMPL_CONTROLLER_FACTORY_HPP

#include <boost/container/flat_map.hpp>
#include "../../controller_factory_base.hpp"
#include <string>
#include <memory>

namespace mochi::http::impl {

    struct controller_comparer {
        inline bool operator()(const std::string& lhs, const std::string& rhs) const {
            return lhs.length() > rhs.length();
        }
    };

    using controller_factories =
        boost::container::flat_map<std::string, std::unique_ptr<controller_factory_base>, controller_comparer>;
    
} // namespace mochi::http::impl

#endif // !MOCHI_HTTP_IMPL_CONTROLLER_FACTORY_HPP