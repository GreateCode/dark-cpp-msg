#pragma once
class message_reader;
#include "message_t.h"
class DARKCPPMSG_API message_reader_t
{
public:
	message_reader_t(void);
	~message_reader_t(void);

private:
	message_reader_t(const message_reader_t& copy);
	message_reader_t operator=(const message_reader_t& copy);
public:

	bool get_message(const char* data,std::size_t size,message_t* p_msg);
protected:
	void release();
	message_reader* _reader;
};

