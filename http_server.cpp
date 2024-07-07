#include "http_server.h"
#include"http_connect.h"
#include<iostream>
#include<memory>
http_server::http_server(boost::asio::io_context& ioc, int port):ioc(ioc),endp(boost::asio::ip::tcp::v4(),port), acc(ioc, endp)
{

    std::cout<<"Waiting for connections"<<std::endl;

}

http_server::~http_server()
{
    std::cout<<"Server stopped"<<std::endl;
}

void http_server::erase_connect(std::shared_ptr<http_connect> con)
{
    cons.erase(con);
}

void http_server::start_accept()
{
    std::shared_ptr<http_connect> con = std::make_shared<http_connect>(asioServerPool::GetInstance()->getIOService(), this);
    std::cout << "Server started on port: " << endp.port()<<endp.address().to_string() << std::endl;
    acc.async_accept(con->get_socket(), std::bind(&http_server::handle_accept, this, std::placeholders::_1,con));
    std::cout << "Waiting for connections" << std::endl;
}

void http_server::handle_accept(boost::system::error_code ec, std::shared_ptr<http_connect> con)
{
    if (ec)
    {
        std::cout<<"Error accepting connection: "<<ec.message()<<std::endl;
        return;
    }
    std::cout<<"New connection accepted"<<std::endl;
    cons.insert(con);
    con->start();
    std::shared_ptr<http_connect> new_con = std::make_shared<http_connect>(asioServerPool::GetInstance()->getIOService(),this);
    acc.async_accept(new_con->get_socket(), std::bind(&http_server::handle_accept, this, std::placeholders::_1,new_con));
}
