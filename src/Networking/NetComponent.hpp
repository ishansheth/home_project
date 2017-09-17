/*
 * NetComponent.hpp
 *
 *  Created on: Apr 10, 2017
 *      Author: ishan
 */

#ifndef SRC_NETWORKING_NETCOMPONENT_HPP_
#define SRC_NETWORKING_NETCOMPONENT_HPP_

#include "../interfaces/IsdkComponent.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

class NetComponent:public IsdkComponent{

std::shared_ptr<boost::asio::io_service> ioservice_;
boost::asio::ip::tcp::resolver resolve;
boost::asio::ip::tcp::socket tcp_socket;
boost::asio::ip::tcp::resolver::query query;
std::array<char,4096> bytes;
std::function<void()> m_componentTask;
std::thread mainloopthread;

public:
NetComponent(Idependencymanager& dp);

void do_resolve()
{
	 resolve.async_resolve(query,[this](const boost::system::error_code &ec,boost::asio::ip::tcp::resolver::iterator iterator)
			 {
		 	 	 resolve_handler(ec,iterator);
			 });
}

 void resolve_handler(const boost::system::error_code &ec,boost::asio::ip::tcp::resolver::iterator iterator)
 {
	 if(!ec){
		 tcp_socket.async_connect(*iterator,[this](const boost::system::error_code &ec){
			 connect_handler(ec);
		 });
	 }else{
 	 	 std::cout<<"in resolve_handler with error"<<std::endl;

	 }
 }

 void connect_handler(const boost::system::error_code &ec)
 {
	 if(!ec){
			std::string r = "GET / HTTP/1.1\r\nHost: highscore.de\r\n\r\n";
			boost::asio::write(tcp_socket,boost::asio::buffer(r));
			tcp_socket.async_read_some(boost::asio::buffer(bytes),[this](const boost::system::error_code &ec, std::size_t bytes_transferred)
					{
						read_handler(ec,bytes_transferred);
					});
	 }else{
 	 	 std::cout<<"in connect_handler with error"<<std::endl;

	 }
 }
 void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred){
	 if(!ec){
		 std::cout.write(bytes.data(),bytes_transferred);
		 tcp_socket.async_read_some(boost::asio::buffer(bytes),[this](const boost::system::error_code &ec, std::size_t bytes_transferred)
				 {
			 	 	 read_handler(ec,bytes_transferred);
				 });

	 }else{
 	 	 std::cout<<"in read_handler with error"<<std::endl;
	 }
 }

 ~NetComponent()
 {
	 if(mainloopthread.joinable())
	 {
		 mainloopthread.join();
	 }
 }

 virtual void start() override;

};

NetComponent::NetComponent(Idependencymanager &dp):
	ioservice_(std::make_shared<boost::asio::io_service>()),
	resolve(*ioservice_),
	tcp_socket(*ioservice_),
	query("highscore.de","80")
{
	(void)dp;
}

void NetComponent::start()
{
	std::cout<<"Netcomponent start"<<std::endl;
	mainloopthread = std::thread([this](){do_resolve();ioservice_->run();});
}

#endif /* SRC_NETWORKING_NETCOMPONENT_HPP_ */
