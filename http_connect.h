#pragma once
#include<boost/beast.hpp>
#include<boost/beast/version.hpp>
#include<boost/asio.hpp>
#include<boost/filesystem.hpp>
#include<memory>
class http_server;
#include"http_server.h"
#include"configMgr.h"
class http_connect:public std::enable_shared_from_this<http_connect>
{
public:
    http_connect(boost::asio::io_context& ioc,http_server* server);
    void start();
    boost::asio::ip::tcp::socket& get_socket();
    ~http_connect();
private:
    http_server* server;
    boost::asio::ip::tcp::socket sock;
    boost::beast::flat_buffer buff;
    boost::beast::http::request<boost::beast::http::dynamic_body> req;
    boost::beast::http::response<boost::beast::http::dynamic_body> res;
    void handle_request();
    void handle_response(boost::system::error_code ec, std::size_t size);
};

