#include "StdAfx.h"
#include "message_reader.h"


message_reader::message_reader(void)
{
	
}


message_reader::~message_reader(void)
{
	
}
bool message_reader::get_message(const char* data,std::size_t size,message_t* p_msg)
{
	std::size_t pos = 0;
	//沒有讀取分配頭 讀取之
	if(!_fragmentation)
	{
		_fragmentation = read_header(data,size,pos);
		if(!_fragmentation)
		{
			return false;
		}
	}

	return false;
}
message_fragmentation_ptr_t message_reader::read_header(const char* data,std::size_t size,std::size_t pos)
{
	if(_datas.empty())
	{

	}
	else
	{
	}
}