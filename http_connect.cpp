#include "http_connect.h"
#include<fstream>
#include <iostream>
http_connect::http_connect(boost::asio::io_context& ioc, http_server* server) :sock(ioc),server(server) {
}
void http_connect::start()
{
    handle_request();
}
boost::asio::ip::tcp::socket& http_connect::get_socket()
{
    return sock;
}
http_connect::~http_connect()
{
    std::cout << "http_connect::~http_connect" << std::endl;
}
void http_connect::handle_request()
{
    boost::beast::http::async_read(sock, buff, req,std::bind(&http_connect::handle_response,this,std::placeholders::_1,std::placeholders::_2));
}

void http_connect::handle_response(boost::system::error_code ec,std::size_t size)
{
    try {
        std::cout << "handle_response-----"<<server->cons.size()<<" "<<sock.remote_endpoint().address()<<":"<<sock.remote_endpoint().port()<<std::endl;
        //std::cout<< sock.remote_endpoint().address().to_string() << "  " << sock.remote_endpoint().port() << std::endl;
        //Êä³öÏß³Ìid
        std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
        res.version(req.version());
        std::cout << "version:" << req.version() << std::endl;
        res.result(boost::beast::http::status::ok);
        std::cout << "result:" << boost::beast::http::status::ok << std::endl;
        res.set(boost::beast::http::field::content_type, "text/html");
        res.keep_alive(false);
        std::cout << "content_type----:" << "text/html" << std::endl;
        configMgr con;
        std::ifstream f;
        std::string path=con["root"];
        path+=req.target();
        f.open(path, std::ios::in);
        if(f.is_open())
        {
            boost::beast::ostream(res.body()) << f.rdbuf();
            std::cout<<path<<std::endl;
        }else
        {
            res.result(boost::beast::http::status::not_found);
            boost::beast::ostream(res.body()) << "not found";
            std::cout<<path<<"not found!"<<std::endl;
        }
        f.close();

        //boost::beast::ostream(res.body()) <<f;

        boost::beast::http::async_write(sock, res, [=](boost::system::error_code ec, std::size_t size)
        {
            std::cout << "handle_response async_write end" << std::endl;
            sock.close();
            server->erase_connect(shared_from_this());
            std::cout << "erase_connect" << std::endl;
        });
        std::cout << "handle_response end" << std::endl;
    }catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}
