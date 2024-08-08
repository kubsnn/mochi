#include "controller_base.hpp"

namespace mochi {

    result controller_base::invoke(beast::http::verb verb, const std::string& route, const std::string& body)
    {
        return methods_[std::pair{ verb, route }](body);
    }

    bool controller_base::has_route(beast::http::verb verb, const std::string& route) const
    {
        return methods_.find(std::pair{ verb, route }) != methods_.end();
    }

    void controller_base::add_route(beast::http::verb verb, const std::string& route, const std::function<result(std::string)>& method)
    {
        methods_.emplace(std::pair{ verb, route }, method);
    }

    void controller_base::add_route(beast::http::verb verb, const std::string& route, const std::function<result()>& method)
    {
        methods_.emplace(std::pair{ verb, route }, [method](std::string body) {
            return method();
        });
    }

}   // namespace app