#include "StdAfx.h"
#include "client_t.h"
#include "client.h"
using namespace dk::net;

client_t::client_t(void)
{
	_client = NULL;

	_func_closed = NULL;
	_func_readed = NULL;
	_func_writed = NULL;

	_id = 0;
}


client_t::~client_t(void)
{
	release();
}
void client_t::connect(const std::string& server,unsigned short port,std::size_t buf,error_t& e)
{
	try
	{
		_client = new client(server,port,buf);
	}
	catch(const boost::system::system_error& se)
	{
		e.value = DK_ERROR_VALUE_SERVER_REJECT;
		e.emsg = se.what();
	}
}
void client_t::run()
{
	if(_client)
	{
		_client->run();
	}
}
void client_t::stop()
{
	_client->stop();
}
void client_t::release()
{
	if(_client)
	{	
		delete _client;
		_client = NULL;

		_func_closed = NULL;
		_func_readed = NULL;
		_func_writed = NULL;
	}
}

void client_t::closed(s_func_closed_t func)
{
	_func_closed = func;
	_client->closed(boost::bind(func,this));
}
void client_t::readed(s_func_readed_t func)
{
	_func_readed = func;
	_client->readed(boost::bind(func,this,_1));
}
void client_t::writed(s_func_writed_t func)
{
	_func_writed = func;
	_client->writed(boost::bind(func,this,_1));
}
	

client_t::s_func_closed_t client_t::closed()
{
	return _func_closed;
}
client_t::s_func_readed_t client_t::readed()
{
	return _func_readed;
}
client_t::s_func_writed_t client_t::writed()
{
	return _func_writed;
}
void client_t::write_message(message_t& msg,error_t& e)
{
	return _client->write_message(msg,e);
}