#pragma once
#ifndef APP_CORE_CONTROLLER_BASE_IMPL_HPP_
#define APP_CORE_CONTROLLER_BASE_IMPL_HPP_
#include <functional>
#include <core/utility/Traits.hpp>
#include <core/mapping/ToJson.hpp>
#include <core/mapping/FromJson.hpp>
#include <json.hpp>
#include <boost/beast.hpp>
#include <core/Result.hpp>
#include <boost/functional/hash.hpp>
#include <core/utility/Hash.hpp>

namespace mochi::core {

    using json = jaszyk::json;
    namespace beast = boost::beast;

    class controller_base;

    template <typename Callable>
    [[maybe_unused]] inline void controller_base::add_route(beast::http::verb verb, const std::string& route, Callable method)
    {
        using ParamType = std::decay_t<typename utility::LambdaTypeExtractor<Callable>::type>;

        methods_.emplace(std::pair{ verb, route }, [method](const std::string& body) -> Result {
            try {
                if constexpr (std::is_same_v<ParamType, void>) {
                    return Result{ beast::http::status::ok, method() };
                } else {
                    ParamType param = mapping::from_json<ParamType>(json::parse(body));
                    return Result{ beast::http::status::ok, method(param) };
                }
            }
            catch (const json::exception& ex) {
                return Result{ beast::http::status::bad_request, std::string(ex.what()) };
            }
        });
    }
    
} // namespace app::core

#endif // !APP_CORE_CONTROLLER_BASE_IMPL_HPP