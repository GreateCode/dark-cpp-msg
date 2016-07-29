#pragma once

//消息分片 頭
typedef struct _MESSAGE_FRAGMENTATION_HEADER_
{
	//消息分片頭 標記 固定為 ^
	char falg[4];

	//消息 唯一標識符
	DWORD id;

	//分片 索引
	WORD order;
	//分片 數據 大小(不包含 分片頭)
	WORD size;

	//分片數量
	DWORD count;
}MESSAGE_FRAGMENTATION_HEADER,*PMESSAGE_FRAGMENTATION_HEADER;

//消息分片
class message_fragmentation
{
public:
	message_fragmentation();
	~message_fragmentation();

	MESSAGE_FRAGMENTATION_HEADER _header;
	std::list<char> _body;
};
typedef boost::shared_ptr<message_fragmentation> message_fragmentation_ptr_t;
