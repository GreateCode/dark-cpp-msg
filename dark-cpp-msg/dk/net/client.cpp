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
	if(_func_closed)
	{
		_func_closed();
	}
}
			
void client::readed(const char* data,std::size_t bytes)
{
	message_t msg;
	if(_reader.get_message(data,bytes,&msg))
	{
		if(_func_readed)
		{
			_func_readed(&msg);
		}
	}
}
			
void client::writed(const boost::system::error_code& e,const char* data,std::size_t bytes)
{
	//”µ“ş‚÷İ” åeÕ` ”àé_ßB½Ó
	if(e)
	{
		//êPé] »ØÕ{
		if(_func_closed)
		{
			_func_closed();
		}

		//êPé]ßB½Ó
		stop();
	}
	else
	{
		if(_func_writed && data[0] == '^')
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