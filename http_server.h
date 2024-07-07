#pragma once
#include<boost/asio.hpp>
#include<boost/beast.hpp>
#include<set>
#include<memory>
class http_connect;
#include"http_connect.h"
#include"asioServerPool.h"
class http_server
{
public:
    http_server(boost::asio::io_context& ioc,int port);
    ~http_server();
    void erase_connect(std::shared_ptr<http_connect> con);
    void start_accept();
    std::set<std::shared_ptr<http_connect>> cons;
private:
    boost::asio::io_context& ioc;
    boost::asio::ip::tcp::endpoint endp;
    boost::asio::ip::tcp::acceptor acc;
    
    void handle_accept(boost::system::error_code ec,std::shared_ptr<http_connect> con);
};

