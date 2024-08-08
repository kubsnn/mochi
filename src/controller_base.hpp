#pragma once
#ifndef MOCHI_CONTROLLER_BASE_HPP
#define MOCHI_CONTROLLER_BASE_HPP

#include "result.hpp"
#include "mapping/to_json.hpp"
#include "mapping/from_json.hpp"
#include "utility/hash.hpp"
#include "json.hpp"
#include <boost/beast.hpp>
#include <unordered_map>
#include <functional>
#include <string>

namespace mochi {

    namespace beast = boost::beast;
    using json = jaszyk::json;

    class controller_base {
        friend class http_session;
    public:
        using methods_map = std::unordered_map<std::pair<beast::http::verb, std::string>, std::function<result(std::string)>>;

        virtual ~controller_base() = default;

        bool has_route(beast::http::verb verb, const std::string& route) const;

        result invoke(beast::http::verb verb, const std::string& route, const std::string& body);

    protected:
        void add_route(beast::http::verb verb, const std::string& route, const std::function<result(std::string)>& method);

        void add_route(beast::http::verb verb, const std::string& route, const std::function<result()>& method);

        // Route that returns object convertable to json using app::mapping::to_json<T>(const T&)
        template <typename Callable>
        [[maybe_unused]] void add_route(beast::http::verb verb, const std::string& route, Callable method);

        methods_map methods_;
    };
    
} // namespace app

#include "impl/controller_base_impl.hpp"

#endif // !MOCHI_CONTROLLER_BASE_HPP