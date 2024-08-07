#pragma once
#ifndef __RESULT_HPP__
#define __RESULT_HPP__

#include <string>
#include <boost/beast.hpp>
#include <core/mapping/ToJson.hpp>
#include <json.hpp>

namespace mochi::core {

    namespace beast = boost::beast;
    using json = jaszyk::json;

    class Result {
    public:
        template <typename T>
        inline Result(beast::http::status status, const T& body) noexcept
            : status_(status), body_(mapping::to_json(body).dump()) 
        { }
        
        [[nodiscard]] inline beast::http::status status() const noexcept { return status_; }
        [[nodiscard]] inline std::string& body() noexcept { return body_; }

    private:
        beast::http::status status_;
        std::string body_;
    };

} // namespace app::core

#endif // !__RESULT_HPP__