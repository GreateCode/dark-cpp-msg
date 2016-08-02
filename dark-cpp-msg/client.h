#pragma once
#include "public.h"
#include "message_t.h"
#include "message_reader_t.h"
class client
	:public dark::net::tcp_client
{
public:
	client(const std::string& server,unsigned short port,std::size_t buf);
	~client(void);

protected:
	virtual void closed();
	virtual void readed(const char* data,std::size_t bytes);
	virtual void writed(const boost::system::error_code& e,const char* data,std::size_t bytes);


	//�¼� ���{
	typedef boost::function<void()> b_func_closed_t;
	typedef boost::function<void(message_t*)> b_func_readed_t;
	typedef boost::function<void(std::size_t)> b_func_writed_t;
	
	b_func_closed_t _func_closed;
	b_func_readed_t _func_readed;
	b_func_writed_t _func_writed;

	message_reader_t _reader;
public:
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
	void write_message(message_t& msg,error_t& e);
};

