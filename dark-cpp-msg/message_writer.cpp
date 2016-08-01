#include "StdAfx.h"
#include "message_writer.h"


message_writer::message_writer(std::size_t size)
{
	_message = new message();

	_fragmentation_order = 0;

	if(size < DARK_MESSAGE_FRAGMENTATION_MIN)
	{
		_size = DARK_MESSAGE_FRAGMENTATION_MIN;
	}
	else if(size > DARK_MESSAGE_FRAGMENTATION_MAX)
	{
		_size = DARK_MESSAGE_FRAGMENTATION_MAX;
	}
	else
	{
		_size = size;
	}
}


message_writer::~message_writer(void)
{
	if(_message)
	{
		delete _message;
		_message = NULL;
	}
}

//壓入數據流
void message_writer::push_data(const char* data,std::size_t size)
{
	for(std::size_t i=0;i<size;++i)
	{
		//沒有分片 創建之
		if(!_fragmentation)
		{
			_fragmentation = boost::make_shared<message_fragmentation_t>();

			PMESSAGE_FRAGMENTATION_HEADER header = _fragmentation->get_header();
			header->order = _fragmentation_order++;
		}

		//寫入數據量
		_fragmentation->push(data[i]);

		//一個分片 填滿 加入消息流
		if(_fragmentation->get_unpack()->_body.size() >= _size)
		{
			_fragmentation->get_unpack()->set_size();
			_message->insert(_fragmentation);
			_fragmentation.reset();
		}
	}
}

//創建 消息
//id 為消息 標識符
void message_writer::create_message(std::size_t id,message_t* p_msg)
{
	//將 未寫入消息的 數據 加入消息流
	if(_fragmentation)
	{
		_fragmentation->get_unpack()->set_size();
		_message->insert(_fragmentation);
		_fragmentation.reset();
	}
	_message->id(id);
	_message->count(_fragmentation_order);

	_message = p_msg->swap(_message);
	if(_message)
	{
		delete _message;
	}
}