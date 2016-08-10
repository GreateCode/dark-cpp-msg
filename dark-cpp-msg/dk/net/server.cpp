#include "StdAfx.h"
#include "server.h"
#include "public.h"
#include "message.h"

using namespace dk::net;

server::server(unsigned short port,std::size_t buf)
	:tcp_server(port,buf)
{
}


server::~server(void)
{
}

void server::get_remote_port(SOCKET s,unsigned short& port,error_t& e)
{
	BOOST_AUTO(find,_handlers.find(s));
	if(find == _handlers.end())
	{
		e.value = DK_ERROR_VALUE_NOT_FOUNT;
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
		e.value = DK_ERROR_VALUE_NOT_FOUNT;
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
		e.value = DK_ERROR_VALUE_NOT_FOUNT;
		e.emsg = "not found socket";
		return;
	}

	write(find->second->_socket,msg.get_unpack()->_data);
	
}

void server::accepted(const boost::system::error_code& e,dark::net::tcp_socket_t s)
{
	client_handler_ptr_t handler = boost::make_shared<client_handler>();
	handler->_socket = s;
	_handlers[s->native()] = handler;

	if(_func_accepted)
	{
		_func_accepted(s->native());
	}
}
	
void server::closed(dark::net::tcp_socket_t s)
{
	if(_func_closed && s->is_open())
	{
		_func_closed(s->native());
	}

	BOOST_AUTO(find,_handlers.find(s->native()));
	if(find != _handlers.end())
	{
		_handlers.erase(find);
	}
}
	
void server::readed(dark::net::tcp_socket_t s,const char* data,std::size_t bytes)
{
	BOOST_AUTO(find,_handlers.find(s->native()));
	if(find == _handlers.end())
	{
		return;
	}
	message_t msg;

	while(find->second->_reader.get_message(data,bytes,&msg))
	{
		if(data)
		{
			data = NULL;
			bytes = 0;
		}

		if(_func_readed)
		{
			_func_readed(s->native(),&msg);
		}

		std::size_t size = 0;
		const char* str = msg.get_body(&size);
		if(size < DK_PROTOCOL_HASH_SIZE)
		{
			continue;
		}
		std::string hash(str,DK_PROTOCOL_HASH_SIZE);
		BOOST_AUTO(find_handler,find->second->_handlers.find(hash));
		if(find_handler != find->second->_handlers.end())
		{
			find_handler->second->handler_message(s->native(),&msg);
		}
	}
}
	
void server::writed(const boost::system::error_code& e,dark::net::tcp_socket_t s,const char* data,std::size_t bytes)
{
	//數據傳輸 錯誤 斷開連接
	if(e)
	{
		//關閉 回調
		if(_func_closed)
		{
			_func_closed(s->native());
		}

		//刪除 客戶記錄
		BOOST_AUTO(find,_handlers.find(s->native()));
		if(find != _handlers.end())
		{
			_handlers.erase(find);
		}

		//關閉連接
		s->close();
	}
	else
	{
		if(_func_writed && data[0] == '^')
		{
			BOOST_AUTO(find,_handlers.find(s->native()));
			if(find != _handlers.end())
			{
				PMESSAGE_HEADER header = (PMESSAGE_HEADER)data;
				_func_writed(s->native(),header->id);
			}
		}
	}
}

void server::register_protocol_handler(SOCKET s,protocol_handler_ptr_t handler)
{
	BOOST_AUTO(find,_handlers.find(s));
	if(find == _handlers.end())
	{
		return;
	}
	find->second->_handlers[handler->get_hash()] = handler;
}