#pragma once
#ifndef MOCHI_CONTROLLER_BASE_IMPL_HPP
#define MOCHI_CONTROLLER_BASE_IMPL_HPP

#include "../utility/traits.hpp"
#include "../utility/hash.hpp"
#include "../mapping/to_json.hpp"
#include "../mapping/from_json.hpp"
#include "../result.hpp"
#include "json.hpp"
#include <boost/beast.hpp>
#include <boost/functional/hash.hpp>
#include <functional>

namespace mochi {

    using json = jaszyk::json;
    namespace beast = boost::beast;

    class controller_base;

    template <typename Callable>
    [[maybe_unused]] inline void controller_base::add_route(beast::http::verb verb, const std::string& route, Callable method)
    {
        using ParamType = std::decay_t<typename utility::LambdaTypeExtractor<Callable>::type>;

        methods_.emplace(std::pair{ verb, route }, [method](const std::string& body) -> result {
            try {
                if constexpr (std::is_same_v<ParamType, void>) {
                    return result{beast::http::status::ok, method() };
                } else {
                    ParamType param = mapping::from_json<ParamType>(json::parse(body));
                    return result{beast::http::status::ok, method(param) };
                }
            }
            catch (const json::exception& ex) {
                return result{beast::http::status::bad_request, std::string(ex.what()) };
            }
        });
    }
    
} // namespace app

#endif // !MOCHI_CONTROLLER_BASE_IMPL_HPP