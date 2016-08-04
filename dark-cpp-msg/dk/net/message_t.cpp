#include "StdAfx.h"
#include "message_t.h"
#include "message.h"
using namespace dk::net;
message_t::message_t(void)
{
	_message = new message();
}


message_t::~message_t(void)
{
	if(_message)
	{
		delete _message;
	}
}

PMESSAGE_HEADER message_t::get_header()const
{
	return _message->get_header();
}
	
const char* message_t::get_body(std::size_t* size)
{
	return _message->get_body(size);
}