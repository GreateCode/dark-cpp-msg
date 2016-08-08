#include "stdafx.h"
#include "file_handler_t.h"
#include "file_handler.h"

using namespace dk::net::protocol;

const std::string g_hash = "e785578f13afe28afd77527f7177db22";
file_handler_t::file_handler_t(void)
{
	_handler = NULL;

	_handler = new file_handler();
}
				
file_handler_t::~file_handler_t(void)
{
	if(_handler)
	{
		delete _handler;
	}
}

				
const std::string& file_handler_t::get_hash()const 
{
	return g_hash;
}
				
bool file_handler_t::handler_message(SOCKET s,dk::net::message_t* p_msg)
{
	return _handler->handler_message(s,p_msg);
}
