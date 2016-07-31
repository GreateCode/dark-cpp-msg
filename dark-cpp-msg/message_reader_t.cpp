#include "StdAfx.h"
#include "message_reader_t.h"
#include "message_reader.h"

message_reader_t::message_reader_t(void)
{
	_reader = new message_reader();
}


message_reader_t::~message_reader_t(void)
{
	release();
}
void message_reader_t::release()
{
	if(_reader)
	{
		delete _reader;
		_reader = NULL;
	}
}

bool message_reader_t::get_message(const char* data,std::size_t size,message_t* p_msg)
{
	return _reader->get_message(data,size,p_msg);
}