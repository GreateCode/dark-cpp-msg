#include "StdAfx.h"
#include "message_writer_t.h"


message_writer_t::message_writer_t(void)
{
	_writer = NULL;
}


message_writer_t::~message_writer_t(void)
{
	release();
}

void message_writer_t::push_data(const char* data,std::size_t size)
{

}

void message_writer_t::create_message(DWORD id,WORD size,message_t* p_msg)
{

}

void message_writer_t::release()
{

}