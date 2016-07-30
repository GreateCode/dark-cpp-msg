#pragma once
#include "fragmentation.h"

//ÏûÏ¢·ÖÆ¬
class message_fragmentation
{
public:
	message_fragmentation();
	~message_fragmentation();

	MESSAGE_FRAGMENTATION_HEADER _header;
	std::deque<char> _body;

	void push(const char c);
};
