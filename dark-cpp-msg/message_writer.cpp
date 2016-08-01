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

//���딵����
void message_writer::push_data(const char* data,std::size_t size)
{
	for(std::size_t i=0;i<size;++i)
	{
		//�]�з�Ƭ ����֮
		if(!_fragmentation)
		{
			_fragmentation = boost::make_shared<message_fragmentation_t>();

			PMESSAGE_FRAGMENTATION_HEADER header = _fragmentation->get_header();
			header->order = _fragmentation_order++;
		}

		//���딵����
		_fragmentation->push(data[i]);

		//һ����Ƭ ��M ������Ϣ��
		if(_fragmentation->get_unpack()->_body.size() >= _size)
		{
			_fragmentation->get_unpack()->set_size();
			_message->insert(_fragmentation);
			_fragmentation.reset();
		}
	}
}

//���� ��Ϣ
//id ����Ϣ ���R��
void message_writer::create_message(std::size_t id,message_t* p_msg)
{
	//�� δ������Ϣ�� ���� ������Ϣ��
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