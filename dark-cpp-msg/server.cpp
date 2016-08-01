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

void server::write_message(SOCKET s,message_t& msg,error_t& e)
{
	BOOST_AUTO(find,_handlers.find(s));
	if(find == _handlers.end())
	{
		e.value = DARK_ERROR_VALUE_NOT_FOUNT;
		e.emsg = "not found socket";
		return;
	}

	
	if(msg.begin())
	{
		//組合消息
		std::list<char> tmp;
		do
		{
			message_fragmentation_t* fragmentation = msg.get();
			PMESSAGE_FRAGMENTATION_HEADER header = fragmentation->get_header();
			//寫入 header
			for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
			{
				tmp.push_back(((char*)header)[i]);
			}
			
			boost::shared_array<char> buf(new char[header->size]);
			std::size_t size = fragmentation->clone_binary(buf.get());
			//寫入 body
			for(std::size_t i=0;i<size;++i)
			{
				tmp.push_back(i);
			}
		}while(msg.next());


		//發送 消息
		buffer_ptr_t buffer = boost::make_shared<std::vector<char>>(tmp.size(),0);
		std::copy(tmp.begin(),tmp.end(),buffer->begin());
		write(find->second->_socket,buffer);
	}
}