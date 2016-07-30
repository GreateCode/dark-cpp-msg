#include "StdAfx.h"
#include "message_writer_t.h"
#include "message_writer.h"

message_writer_t::message_writer_t(std::size_t size)
{
	_size = size;
	_writer = new message_writer(size);
}


message_writer_t::~message_writer_t(void)
{
	release();
}

void message_writer_t::push_data(const char* data,std::size_t size)
{
	_writer->push_data(data,size);
}

void message_writer_t::create_message(DWORD id,message_t* p_msg)
{
	_writer->create_message(id,p_msg);

	//創建新的 寫入流
	release();
	_writer = new message_writer(_size);
}

void message_writer_t::release()
{
	if(_writer)
	{
		delete _writer;
		_writer = NULL;
	}
}