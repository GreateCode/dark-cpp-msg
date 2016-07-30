#include "StdAfx.h"
#include "message_fragmentation_t.h"
#include "message_fragmentation.h"

message_fragmentation_t::message_fragmentation_t(void)
{
	_fragmentation = new message_fragmentation();

	_fragmentation = NULL;
}


message_fragmentation_t::~message_fragmentation_t(void)
{
	release();
}
PMESSAGE_FRAGMENTATION_HEADER message_fragmentation_t::get_header()
{
	if(_fragmentation)
	{
		return &(_fragmentation->_header);
	}
	return NULL;
}

	
void message_fragmentation_t::release()
{
	if(_fragmentation)
	{
		delete _fragmentation;
		_fragmentation = NULL;
	}
}
//Œ‘Èë”µ“şÁ÷
void message_fragmentation_t::push(const char c)
{
	_fragmentation->push(c);
}