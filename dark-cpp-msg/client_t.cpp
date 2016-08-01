#include "StdAfx.h"
#include "client_t.h"
#include "client.h"

client_t::client_t()
{
	_client = NULL;

	_func_closed = NULL;
	_func_readed = NULL;

	_id = 0;
}


client_t::~client_t(void)
{
	release();
}
void client_t::connect(const std::string& server,unsigned short port,std::size_t buf,error_t& e)
{
	_client = new client(server,port,buf,e);
	if(e)
	{
		release();
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
	

client_t::s_func_closed_t client_t::closed()
{
	return _func_closed;
}
client_t::s_func_readed_t client_t::readed()
{
	return _func_readed;
}
void client_t::write_message(message_t& msg,error_t& e)
{
	return _client->write_message(msg,e);
}