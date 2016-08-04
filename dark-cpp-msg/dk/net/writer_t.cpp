#include "StdAfx.h"
#include "writer_t.h"

#include "writer.h"
using namespace dk::net;

writer_t::writer_t(void)
{
	_writer = NULL;
	_writer = new writer();
}


writer_t::~writer_t(void)
{
	if(_writer)
	{
		delete _writer;
	}
}
void writer_t::push_data(const char* data,std::size_t size)
{
	_writer->push_data(data,size);
}

void writer_t::create_message(std::size_t id,message_t* p_msg)
{
	_writer->create_message(id,p_msg->get_unpack());
}