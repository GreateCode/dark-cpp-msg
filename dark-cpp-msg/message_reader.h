#pragma once
#include "message_t.h"
#include "message.h"
class message_reader
{
public:
	message_reader(void);
	~message_reader(void);

	//寫入數據流到消息
	//如果 成功接收到一條完整消息 返回 ture 並將消息返回到p_msg
	//否則 返回 false
	bool get_message(const char* data,std::size_t size,message_t* p_msg);

protected:
	//讀取 緩衝區
	std::deque<char> _datas;

	//當前分片
	message_fragmentation_ptr_t _fragmentation;

	message_fragmentation_ptr_t read_header(const char* data,std::size_t size,std::size_t pos);
};

