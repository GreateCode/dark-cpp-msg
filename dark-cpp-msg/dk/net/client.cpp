#include "StdAfx.h"
#include "client.h"
#include "message.h"
using namespace dk::net;

client::client(const std::string& server,unsigned short port,std::size_t buf)
	:tcp_client(server,port,buf)
{
}


client::~client(void)
{
}
void client::closed()
{
	if(_func_closed && is_open())
	{
		_func_closed();
	}
}
			
void client::readed(const char* data,std::size_t bytes)
{
	message_t msg;
	while(_reader.get_message(data,bytes,&msg))
	{
		if(data)
		{
			data = NULL;
			bytes = 0;
		}

		if(_func_readed)
		{
			_func_readed(&msg);
		}


		std::size_t size = 0;
		const char* str = msg.get_body(&size);
		if(size < DK_PROTOCOL_HASH_SIZE)
		{
			return;
		}
		std::string hash(str,DK_PROTOCOL_HASH_SIZE);
		BOOST_AUTO(find,_handlers.find(hash));
		if(find != _handlers.end())
		{
			find->second->handler_message(0,&msg);
		}
	}
}
			
void client::writed(const boost::system::error_code& e,const char* data,std::size_t bytes)
{
	//”µ“þ‚÷Ý” åeÕ` ”àé_ßB½Ó
	if(e)
	{
		//êPé] »ØÕ{
		if(_func_closed && is_open())
		{
			_func_closed();
		}

		//êPé]ßB½Ó
		stop();
	}
	else
	{
		if(_func_writed && 
			bytes > 4 && 
			data[0] == DK_MESSAGE_HEADER_FLAG_0 &&
			data[1] == DK_MESSAGE_HEADER_FLAG_1 &&
			data[2] == DK_MESSAGE_HEADER_FLAG_2 &&
			data[3] == DK_MESSAGE_HEADER_FLAG_3)
		{
			PMESSAGE_HEADER header = (PMESSAGE_HEADER)data;
			_func_writed(header->id);
		}
	}
}
void client::write_message(message_t& msg,error_t& e)
{
	write(msg.get_unpack()->_data);
}
void client::register_protocol_handler(protocol_handler_ptr_t handler)
{
	_handlers[handler->get_hash()] = handler;
}