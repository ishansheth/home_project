/*
 * NetComponent.hpp
 *	The net component which has a functionality of resolving
 *	the URL initialized in the query
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

boost::asio::io_service& ioservice_;
boost::asio::ip::tcp::resolver resolve;
boost::asio::ip::tcp::socket tcp_socket;
boost::asio::ip::tcp::resolver::query query;
std::array<char,4096> bytes;
std::function<void()> m_componentTask;
std::string resolveURL;

public:
NetComponent(Idependencymanager& dp,boost::asio::io_service&,const std::string&);

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
			std::string r = "GET / HTTP/1.1\r\nHost:"+ resolveURL +"\r\n\r\n";
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
 }

 virtual void start() override{
		do_resolve();
		std::cout<<"Netcomponent start"<<std::endl;
 }

};

NetComponent::NetComponent(Idependencymanager &dp,boost::asio::io_service& ioser,const std::string& urlstring):
	ioservice_(ioser),
	resolve(ioser),
	tcp_socket(ioser),
	resolveURL(urlstring),
	query(urlstring,"80")
{
	(void)dp;
}


#endif /* SRC_NETWORKING_NETCOMPONENT_HPP_ */
