#pragma once
#include "fragmentation.h"

//��Ϣ��Ƭ
class message_fragmentation
{
public:
	message_fragmentation();
	~message_fragmentation();

	MESSAGE_FRAGMENTATION_HEADER _header;
	std::deque<char> _body;

	void push(const char c);
	//���� body ���� �� �D�x�ַ� ߀ԭ
	std::size_t clone(char* out);
	//���� body ���� ��߀ԭ �D�x�ַ� 
	std::size_t clone_binary(char* out);

	inline void set_size()
	{
		_header.size = _body.size();
	}

protected:
	char get_c(std::size_t& pos);
};
