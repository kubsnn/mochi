#pragma once
#ifndef MOCHI_CORE_CONTROLLER_BASE_HPP
#define MOCHI_CORE_CONTROLLER_BASE_HPP

#include <core/Result.hpp>
#include <core/mapping/ToJson.hpp>
#include <core/mapping/FromJson.hpp>
#include <core/utility/Hash.hpp>
#include <unordered_map>
#include <boost/beast.hpp>
#include <json.hpp>
#include <functional>
#include <string>

namespace mochi::core {

    namespace beast = boost::beast;
    using json = jaszyk::json;

    class controller_base {
        friend class HttpSession;
    public:
        using methods_map = std::unordered_map<std::pair<beast::http::verb, std::string>, std::function<Result(std::string)>>;

        virtual ~controller_base() = default;

        bool has_route(beast::http::verb verb, const std::string& route) const;

        Result invoke(beast::http::verb verb, const std::string& route, const std::string& body);

    protected:
        void add_route(beast::http::verb verb, const std::string& route, const std::function<Result(std::string)>& method);

        void add_route(beast::http::verb verb, const std::string& route, const std::function<Result()>& method);

        // Route that returns object convertable to json using app::core::mapping::to_json<T>(const T&)
        template <typename Callable>
        [[maybe_unused]] void add_route(beast::http::verb verb, const std::string& route, Callable method);

        methods_map methods_;
    };
    
} // namespace app::core

#include <core/impl/ControllerBaseImpl.hpp>

#endif // !MOCHI_CORE_CONTROLLER_BASE_HPP