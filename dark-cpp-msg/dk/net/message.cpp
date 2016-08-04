#include "StdAfx.h"
#include "message.h"
using namespace dk::net;

message::message(void)
{
	
}


message::~message(void)
{
}

PMESSAGE_HEADER message::get_header()const
{
	if(!_data)
	{
		return NULL;
	}
	return (PMESSAGE_HEADER)(_data->data());
}

const char* message::get_body(std::size_t* size)
{
	if(!_data)
	{
		return NULL;
	}
	std::size_t tmp = _data->size() - sizeof(MESSAGE_HEADER);
	if(size)
	{
		*size = tmp;
	}
	if(!tmp)
	{
		return NULL;
	}
	return _data->data() + sizeof(MESSAGE_HEADER);
}