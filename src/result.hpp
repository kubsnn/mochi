#pragma once
#ifndef MOCHI_RESULT_HPP
#define MOCHI_RESULT_HPP

#include "mapping/to_json.hpp"
#include <string>
#include <boost/beast.hpp>
#include "json.hpp"

namespace mochi {

    namespace beast = boost::beast;
    using json = jaszyk::json;

    class result {
    public:
        template <typename T>
        inline result(beast::http::status status, const T& body) noexcept
            : status_(status), body_(mapping::to_json(body).dump()) 
        { }
        
        [[nodiscard]] inline beast::http::status status() const noexcept { return status_; }
        [[nodiscard]] inline std::string& body() noexcept { return body_; }

    private:
        beast::http::status status_;
        std::string body_;
    };

} // namespace app

#endif // !MOCHI_RESULT_HPP