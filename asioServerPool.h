#pragma once
#include"Singleton.h"
#include<boost/asio.hpp>
#include<vector>
#include<iostream>
class asioServerPool:public Singleton<asioServerPool>
{
	friend class Singleton<asioServerPool>;
public:
	boost::asio::io_context& getIOService();
	~asioServerPool();
	void stop();
private:
	asioServerPool(std::size_t size=2);
	asioServerPool(asioServerPool const&) = delete;
	asioServerPool& operator=(asioServerPool const&) = delete;
	std::vector<boost::asio::io_context> _ioServices;
	std::vector<std::unique_ptr<boost::asio::io_context::work>> _workes;
	std::vector<std::thread> _threads;
	std::size_t _nextServiceIndex;


};

