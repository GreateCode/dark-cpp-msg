#pragma once
class message_reader;
#include "message_t.h"
class DARKCPPMSG_API message_reader_t
{
public:
	message_reader_t(void);
	~message_reader_t(void);


	bool get_message(const char* data,std::size_t size,message_t* p_msg);
protected:
	void release();
	message_reader* _reader;
};

