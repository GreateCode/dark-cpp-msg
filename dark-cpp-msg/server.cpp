#include "StdAfx.h"
#include "server.h"

using namespace dark::net;

server::server(unsigned short port,std::size_t buf)
	:tcp_server(port,buf)
{
}


server::~server(void)
{

}

void server::accepted(const boost::system::error_code& e,tcp_socket_t s)
{
	client_handler_ptr_t handler = boost::make_shared<client_handler>();
	handler->_socket = s;
	_handlers[s->native()] = handler;

	if(_func_accepted)
	{
		_func_accepted(s->native());
	}
}

void server::closed(tcp_socket_t s)
{
	if(_func_closed)
	{
		_func_closed(s->native());
	}

	BOOST_AUTO(find,_handlers.find(s->native()));
	if(find != _handlers.end())
	{
		_handlers.erase(find);
	}

}

void server::readed(tcp_socket_t s,const char* data,std::size_t bytes)
{

}

void server::writed(const boost::system::error_code& e,tcp_socket_t s,const char* data,std::size_t bytes)
{

}

void server::get_remote_port(SOCKET s,unsigned short& port,error_t& e)
{
	BOOST_AUTO(find,_handlers.find(s));
	if(find == _handlers.end())
	{
		e.value = DARK_ERROR_VALUE_NOT_FOUNT;
		e.emsg = "not found socket";
		return;
	}
	port = find->second->_socket->remote_endpoint().port();
}
	
void server::get_remote_address(SOCKET s,std::string& address,error_t& e)
{
	BOOST_AUTO(find,_handlers.find(s));
	if(find == _handlers.end())
	{
		e.value = DARK_ERROR_VALUE_NOT_FOUNT;
		e.emsg = "not found socket";
		return;
	}
	address = find->second->_socket->remote_endpoint().address().to_string();
}