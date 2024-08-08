#include "http_session.hpp"
#include "../logger.hpp"
#include <iostream>
#include <string_view>
#include <thread>

namespace mochi {

    std::shared_ptr<beast::http::response<beast::http::string_body>> buildResponse(result& result)
    {
        auto response = std::make_shared<beast::http::response<beast::http::string_body>>();

        response->body() = std::move(result.body());
        response->result(result.status());
        response->version(11);
        response->set(beast::http::field::content_type, "application/json");
        response->prepare_payload();

        return response;
    }

    std::shared_ptr<beast::http::response<beast::http::string_body>> buildResponse(beast::http::status status, std::string body)
    {
        auto response = std::make_shared<beast::http::response<beast::http::string_body>>();

        response->body() = std::move(body);
        response->result(status);
        response->version(11);
        response->set(beast::http::field::content_type, "application/json");
        response->prepare_payload();

        return response;
    }

    http_session::http_session(tcp::socket socket, controller_factories& controllerFactories, const dependency_resolver& injector)
        : stream_(std::move(socket)), controllerFactories_(controllerFactories), injector_(injector)
    { }

    http_session::~http_session() = default;

    void http_session::run()
    {
        doRead();
    }

    std::shared_ptr<beast::http::response<beast::http::string_body>> http_session::invoke(std::unique_ptr<controller_base> controller, const std::string& route)
    {
        try {
            auto result = controller->invoke(req_.method(), route, req_.body());

            return buildResponse(result);
        }
        catch (const std::bad_variant_access& ex) {
            return buildResponse(beast::http::status::bad_request, "\"Invalid input format.\"" );
        }
    }

    void http_session::doRead()
    {
        auto self = shared_from_this();
        stream_.expires_after(std::chrono::seconds(5));

        beast::http::async_read(stream_, buffer_, req_,
            [self](beast::error_code ec, std::size_t bytes_transferred) {
                self->onRead(ec, bytes_transferred);
            });
    }

    void http_session::onRead(beast::error_code ec, std::size_t bytes_transferred)
    {
        if (ec) return;
        auto [route, controller] = findController();

        if (controller == nullptr) {
            res_ = buildResponse(beast::http::status::not_found, "\"Not found.\"");
            doWrite();
            return;
        }

        res_ = invoke(std::move(controller), route);

        doWrite();
    }

    void http_session::doWrite()
    {
        beast::http::async_write(stream_, *res_,
            [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
                self->onWrite(ec, bytes_transferred);
            });
    }


    void http_session::onWrite(beast::error_code ec, std::size_t bytes_transferred /*, bool close*/)
    {
        if (ec) return;

//        if (close) {
//            beast::error_code ec;
//            stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
//            return;
//        }

        // Clear the request and response for the next iteration
        req_ = {};
        res_ = nullptr;

        doRead();
    }

    std::pair<std::string, std::unique_ptr<controller_base>> http_session::findController()
    {
        for (auto& [route, factory] : controllerFactories_) {
            if (req_.target().starts_with(route)) {
                auto scope = injector_.make_scope();
                auto controller = factory->create(injector_, scope);
                auto sub_route = req_.target().substr(route.size()).to_string();

                if (controller->has_route(req_.method(), sub_route)) {
                    return { std::move(sub_route), std::move(controller) };
                }
            }
        }

        return { "", nullptr };
    }

} // namespace app
