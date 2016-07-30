#include "StdAfx.h"
#include "message_fragmentation.h"


message_fragmentation::message_fragmentation(void)
{
	memset(&_header,0,sizeof(_header));
}


message_fragmentation::~message_fragmentation(void)
{
}
void message_fragmentation::push(const char c)
{
	if('^' == c)
	{
		_body.push_back('\\');
		_body.push_back('[');
		return;
	}
	
	if('\\' == c)
	{
		_body.push_back('\\');
		_body.push_back(']');
		return;
	}

	_body.push_back(c);
}