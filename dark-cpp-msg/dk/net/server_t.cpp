#include "StdAfx.h"
#include "server_t.h"
#include "server.h"
using namespace dk::net;

server_t::server_t(void)
{
	_func_accepted = NULL;
	_func_closed = NULL;
	_func_readed = NULL;
	_func_writed = NULL;

	_server = NULL;

	_id = 0;
}


server_t::~server_t(void)
{
	release();
}

void server_t::write_message(SOCKET s,message_t& msg,error_t& e)
{
	_server->write_message(s,msg,e);
}

void server_t::create(unsigned short port,std::size_t buf,error_t& e)
{
	try
	{
		_server = new server(port,buf);
	}
	catch(const boost::system::system_error& se)
	{
		e.value = DK_ERROR_VALUE_LISTEN_ERROR;
		e.emsg = se.what();
	}
}

void server_t::run()
{
	if(_server)
	{
		_server->run();
	}
}
void server_t::stop()
{
	_server->stop();
}
void server_t::release()
{
	if(_server)
	{
		delete _server;
		_server = NULL;

		_func_accepted = NULL;
		_func_closed = NULL;
		_func_readed = NULL;
		_func_writed = NULL;
	}
}
void server_t::accepted(s_func_accepted_t func)
{
	if(_server)
	{
		_server->accepted(boost::bind(func,this,_1));
	}
}
	
void server_t::closed(s_func_closed_t func)
{
	if(_server)
	{
		_server->closed(boost::bind(func,this,_1));
		
	}
}

void server_t::readed(s_func_readed_t func)
{
	if(_server)
	{
		_server->readed(boost::bind(func,this,_1,_2));
	}
}

void server_t::writed(s_func_writed_t func)
{
	if(_server)
	{
		_server->writed(boost::bind(func,this,_1,_2));
	}
}


	
	
server_t::s_func_accepted_t server_t::accepted()
{
	return _func_accepted;
}
	
server_t::s_func_closed_t server_t::closed()
{
	return _func_closed;
}
	
server_t::s_func_readed_t server_t::readed()
{
	
	return _func_readed;
}
	
server_t::s_func_writed_t server_t::writed()
{
	return _func_writed;
}
void server_t::get_remote_port(SOCKET s,unsigned short& port,error_t& e)
{
	if(!_server)
	{
		e.value = DK_ERROR_VALUE_MEMORY_EMPTY;
		e.emsg = "memory is empty";
		return;
	}
	_server->get_remote_port(s,port,e);
}
	
void server_t::get_remote_address(SOCKET s,std::string& address,error_t& e)
{
	if(!_server)
	{
		e.value = DK_ERROR_VALUE_MEMORY_EMPTY;
		e.emsg = "memory is empty";
		return;
	}
	_server->get_remote_address(s,address,e);
}
