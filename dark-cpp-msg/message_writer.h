#pragma once
#include "message_t.h"
#include "message.h"
#include "message_fragmentation.h"

#define DARK_MESSAGE_FRAGMENTATION_MIN	10
#define DARK_MESSAGE_FRAGMENTATION_MAX	0xFFF0

class message_writer
{
public:
	//size 為分片 大小 此值只 作為 參考 實際值 可能不一致
	message_writer(std::size_t size);
	~message_writer(void);

protected:
	std::size_t _size;

	//寫入流
	std::deque<char> _datas;

	//消息
	message* _message;

	//當前分片 分片大小 order
	message_fragmentation_ptr_t _fragmentation;
	std::size_t _fragmentation_order;
public:
	//壓入數據流
	void push_data(const char* data,std::size_t size);

	//創建 消息
	//id 為消息 標識符
	void create_message(DWORD id,message_t* p_msg);
};

