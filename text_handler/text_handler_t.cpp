#include "StdAfx.h"
#include "text_handler_t.h"
using namespace dk::net::protocol;

extern const std::string g_hash = "e5600412de0ad3cd63c0cc823ecdaa1d";
text_handler_t::text_handler_t(void)
{
}


text_handler_t::~text_handler_t(void)
{
}

const std::string& text_handler_t::get_hash()const
{
	return g_hash;
}
			
bool text_handler_t::handler_message(SOCKET s,dk::net::message_t* p_msg)
{
	std::size_t size = 0;
	const char* ptr = p_msg->get_body(&size);
	std::string str(ptr + DK_PROTOCOL_HASH_SIZE,size - DK_PROTOCOL_HASH_SIZE);
	if(s)
	{	
		std::cout<<"recv text ("<<s<<") : "<<str<<"\n";
	}
	else
	{
		std::cout<<"recv text : "<<str<<"\n";
	}
	return true;
}