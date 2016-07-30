#pragma once
#include "message_fragmentation_t.h"
class message;
class DARKCPPMSG_API message_t
{
public:
	message_t(void);
	~message_t(void);

	//返回分片數量
	std::size_t size()const;
	
	//返回消息是否為空
	bool empty()const;
	

	//分片游標 移動到第一個位置
	//返回 是否 未達到 end (如 _nodes 為空時)
	bool begin();
	
	//分片游標 下移  
	//返回 移動後 是否 未達到 end
	bool next();

	//返回游標 是否 為達到 end
	bool has_next();

	//返回 游標分片
	message_fragmentation_t* get();

	
	inline operator bool()const
	{
		return _message != NULL;
	}
	inline message* get_unpack()const
	{
		return _message;
	}
	void create();
	void release();

	message* swap(message* ptr);
protected:
	message* _message;

};

