#include "StdAfx.h"
#include "reader_t.h"
#include "reader.h"
using namespace dk::net;

reader_t::reader_t(void)
{
	_reader = NULL;
	_reader = new reader();
}


reader_t::~reader_t(void)
{
	if(_reader)
	{
		delete _reader;
	}
}
bool reader_t::get_message(const char* data,std::size_t size,message_t* p_msg)
{
	return _reader->get_message(data,size,p_msg->get_unpack());
}