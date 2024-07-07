#include "asioServerPool.h"

boost::asio::io_context& asioServerPool::getIOService()
{
	if (_nextServiceIndex >= _ioServices.size())_nextServiceIndex = 0;
	std::cout << "AsioIOServicePool::getIOService() index=" << _nextServiceIndex << std::endl;
	return _ioServices[_nextServiceIndex++];
}

asioServerPool::~asioServerPool()
{
	stop();
	std::cout << "AsioIOServicePool::~AsioIOServicePool()" << std::endl;

}

void asioServerPool::stop()
{
	for (int i = 0; i < _ioServices.size(); i++)
	{
		_ioServices[i].stop();
		_workes[i].reset();
	}
	for (auto& t : _threads)
	{
		t.join();
	}
}
asioServerPool::asioServerPool(std::size_t size) :_ioServices(size), _workes(size), _nextServiceIndex(0)
{
	for (std::size_t i = 0; i < size; ++i) {
		_workes[i] = std::unique_ptr<boost::asio::io_context::work>(new boost::asio::io_context::work(_ioServices[i]));
	}
	//遍历多个ioservice，创建多个线程，每个线程内部启动ioservice
	for (std::size_t i = 0; i < _ioServices.size(); ++i) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}
