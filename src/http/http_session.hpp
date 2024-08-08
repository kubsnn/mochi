#pragma once
#ifndef MOCHI_HTTP_SESSION_HPP
#define MOCHI_HTTP_SESSION_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/container/flat_map.hpp>
#include "../controller_factory_base.hpp"
#include "../dependency_resolver.hpp"
#include "http_server.hpp"
#include <memory>

namespace mochi {

    namespace asio = boost::asio;
    namespace beast = boost::beast;

    using tcp = asio::ip::tcp;

    class http_session : public std::enable_shared_from_this<http_session> {
        using controller_factories = http_server::controller_factories;
        template <typename T>
        using response = beast::http::response<T>;
        using string_body = beast::http::string_body;

    public:
        http_session(tcp::socket socket, controller_factories& controllerFactories, const dependency_resolver& injector);
        ~http_session();

        inline http_session operator=(const http_session&) = delete;
        inline http_session operator=(http_session&&) noexcept = delete;

        void run();

    private:
        std::shared_ptr<response<string_body>> invoke(std::unique_ptr<controller_base> controller, const std::string& route);

        void doRead();
        void onRead(beast::error_code ec, std::size_t bytes_transferred);

        void doWrite();
        void onWrite(beast::error_code ec, std::size_t bytes_transferred/*, bool close*/);

        std::pair<std::string, std::unique_ptr<controller_base>> findController();

        beast::tcp_stream stream_;
        beast::flat_buffer buffer_;
        controller_factories& controllerFactories_;
        std::shared_ptr<std::string const> doc_root_;
        beast::http::request<beast::http::string_body> req_;
        std::shared_ptr<beast::http::response<beast::http::string_body>> res_;
        const dependency_resolver& injector_;
    };

}

#endif // !MOCHI_HTTP_SESSION_HPP