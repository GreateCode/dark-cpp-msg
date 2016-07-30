#pragma once
#include "message_t.h"
class message_writer;
class DARKCPPMSG_API message_writer_t
{
public:
	//size 為分片 大小 此值只 作為 參考 實際值 可能不一致
	message_writer_t(std::size_t size);
	~message_writer_t(void);

	//壓入數據流
	void push_data(const char* data,std::size_t size);

	//創建 消息
	//id 為消息 標識符
	void create_message(DWORD id,message_t* p_msg);

protected:
	std::size_t _size;
	void release();
	message_writer* _writer;
};

