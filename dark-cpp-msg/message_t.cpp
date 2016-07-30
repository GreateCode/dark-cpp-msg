#include "StdAfx.h"
#include "message_t.h"
#include "message.h"

message_t::message_t(void)
{
	_message = NULL;
}


message_t::~message_t(void)
{
	release();
}
void message_t::create(void)
{
	if(_message)
	{
		return;
	}
	_message = new message();
}
void message_t::release()
{
	if(_message)
	{
		delete _message;
		_message = NULL;
	}
}

std::size_t message_t::size()const
{
	return _message->size();
}
	
//返回消息是否為空
bool message_t::empty()const
{
	return _message->empty();
}

//分片游標 移動到第一個位置
//返回 是否 未達到 end (如 _nodes 為空時)
bool message_t::begin()
{
	return _message->begin();
}
	
//分片游標 下移  
//返回 移動後 是否 未達到 end
bool message_t::next()
{
	return _message->next();
}

//返回游標 是否 為達到 end
bool message_t::has_next()
{
	return _message->has_next();
}

//返回 游標分片
message_fragmentation_t* message_t::get()
{
	return _message->get();
}

message* message_t::swap(message* ptr)
{
	message* tmp = _message;
	_message = ptr;
	return tmp;
}
