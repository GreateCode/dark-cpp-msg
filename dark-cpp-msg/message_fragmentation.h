#pragma once
#include "fragmentation.h"

//消息分片
class message_fragmentation
{
public:
	message_fragmentation();
	~message_fragmentation();

	MESSAGE_FRAGMENTATION_HEADER _header;
	std::deque<char> _body;

	void push(const char c);
	//返回 body 數據 將 轉義字符 還原
	std::size_t clone(char* out);
	//返回 body 數據 不還原 轉義字符 
	std::size_t clone_binary(char* out);

	inline void set_size()
	{
		_header.size = _body.size();
	}

protected:
	char get_c(std::size_t& pos);
};
