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
	typedef std::deque<char>::iterator iterator_t;

	//已讀完的 分片
	std::map<WORD/*order*/,message_fragmentation_ptr_t> _fragmentations;
	//保存 消息頭
	message_fragmentation_ptr_t _fragmentation_header;

	//尋找 第一個 分片頭 並且刪除 錯誤數據 (分片頭 之前的 數據)
	//返回 true 早到分片頭 false 未找到
	bool find_reader();

	//當前分片
	message_fragmentation_ptr_t _fragmentation;
	bool get_message(message_t* p_msg);
	bool create_message(message_t* p_msg);

	void reset();
	message_fragmentation_ptr_t read_header();
};

