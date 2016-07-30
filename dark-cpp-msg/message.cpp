#include "StdAfx.h"
#include "message.h"


message::message(void)
{
}


message::~message(void)
{
}
void message::id(std::size_t n)
{
	_id = n;
	BOOST_FOREACH(auto& fragmentation,_fragmentations)
	{
		fragmentation.second->get_header()->id = n;
	}
}
	
void message::count(std::size_t n)
{
	_count = n;
	BOOST_FOREACH(auto& fragmentation,_fragmentations)
	{
		fragmentation.second->get_header()->count = n;
	}
}