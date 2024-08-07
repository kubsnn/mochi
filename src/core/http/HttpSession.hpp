#pragma once
#ifndef APP_CORE_HTTPSESSION_HPP
#define APP_CORE_HTTPSESSION_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/container/flat_map.hpp>
#include <core/IControllerFactory.hpp>
#include <core/http/HttpServer.hpp>
#include <core/dependency_resolver.hpp>
#include <memory>

namespace mochi::core {

    namespace asio = boost::asio;
    namespace beast = boost::beast;

    using tcp = asio::ip::tcp;

    class HttpSession : public std::enable_shared_from_this<HttpSession> {
        using controller_factories = HttpServer::controller_factories;
        template <typename T>
        using response = beast::http::response<T>;
        using string_body = beast::http::string_body;

    public:
        HttpSession(tcp::socket socket, controller_factories& controllerFactories, const dependency_resolver& injector);
        ~HttpSession();

        inline HttpSession operator=(const HttpSession&) = delete;
        inline HttpSession operator=(HttpSession&&) noexcept = delete;

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

#endif // !APP_CORE_HTTPSESSION_HPP