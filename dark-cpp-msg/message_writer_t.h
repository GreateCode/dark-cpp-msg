#pragma once
#include "message_t.h"
class message_writer;
class DARKCPPMSG_API message_writer_t
{
public:
	message_writer_t(void);
	~message_writer_t(void);

	//壓入數據量
	void push_data(const char* data,std::size_t size);

	//創建 消息
	//id 為消息 標識符
	//size 為分片 大小 此值只 作為 參考 實際值 可能不一致
	void create_message(DWORD id,WORD size,message_t* p_msg);

	void release();
private:
	message_writer* _writer;
};

