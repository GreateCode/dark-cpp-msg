#pragma once

#include "public.h"
#include "client_handler.h"
#include "message_t.h"
class server
	:public dark::net::tcp_server
{
public:
	server(unsigned short port,std::size_t buf);
	~server(void);

	virtual void accepted(const boost::system::error_code& e,dark::net::tcp_socket_t s);
	virtual void closed(dark::net::tcp_socket_t s);
	virtual void readed(dark::net::tcp_socket_t s,const char* data,std::size_t bytes);
	virtual void writed(const boost::system::error_code& e,dark::net::tcp_socket_t s,const char* data,std::size_t bytes);
	
protected:
	//事件 回調
	typedef boost::function<void(SOCKET)> b_func_accepted_t;
	typedef b_func_accepted_t b_func_closed_t;
	typedef boost::function<void(SOCKET,message_t*)> b_func_readed_t;
	typedef boost::function<void(SOCKET,std::size_t)> b_func_writed_t;

	b_func_accepted_t _func_accepted;
	b_func_closed_t _func_closed;
	b_func_readed_t _func_readed;
	b_func_writed_t _func_writed;

public:
	inline void accepted(b_func_accepted_t func)
	{
		_func_accepted = func;
	}
	inline void closed(b_func_closed_t func)
	{
		_func_closed = func;
	}
	inline void readed(b_func_readed_t func)
	{
		_func_readed = func;
	}
	inline void writed(b_func_writed_t func)
	{
		_func_writed = func;
	}
	

protected:
	//已連接 客戶端
	boost::unordered_map<SOCKET,client_handler_ptr_t> _handlers;
	
public:
	void get_remote_port(SOCKET s,unsigned short& port,error_t& e);
	void get_remote_address(SOCKET s,std::string& address,error_t& e);

	void write_message(SOCKET s,message_t& msg,error_t& e);
};

