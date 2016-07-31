#include "StdAfx.h"
#include "message_fragmentation.h"


message_fragmentation::message_fragmentation(void)
{
	memset(&_header,0,sizeof(_header));
	_header.falg[0] = '^';
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

std::size_t message_fragmentation::clone(char* out)
{
	std::size_t sum = 0;

	for(std::size_t pos=0;pos<_body.size();)
	{
		out[sum++] = get_c(pos);
	}

	return sum;
}
char message_fragmentation::get_c(std::size_t& pos)
{
	char c = _body[pos++];
	if(pos == _body.size())
	{
		return c;
	}

	if('\\' == c)
	{
		char tmp = _body[pos];
		if('[' == tmp)
		{
			c = '^';
			++pos;
		}
		else if(']' == tmp)
		{
			//c = '\\';
			++pos;
		}
	}
	return c;
}