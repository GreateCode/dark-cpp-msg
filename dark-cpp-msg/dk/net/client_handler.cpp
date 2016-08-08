#include "StdAfx.h"
#include "client_handler.h"
using namespace dk::net;

client_handler::client_handler(void)
{
}


client_handler::~client_handler(void)
{
}
	
void client_handler::register_protocol_handler(protocol_handler_ptr_t handler)
{
	_handlers[handler->get_hash()] = handler;
}