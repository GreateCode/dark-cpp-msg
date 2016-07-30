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
	
//������Ϣ�Ƿ���
bool message_t::empty()const
{
	return _message->empty();
}

//��Ƭ�Θ� �Ƅӵ���һ��λ��
//���� �Ƿ� δ�_�� end (�� _nodes ��Օr)
bool message_t::begin()
{
	return _message->begin();
}
	
//��Ƭ�Θ� ����  
//���� �Ƅ��� �Ƿ� δ�_�� end
bool message_t::next()
{
	return _message->next();
}

//�����Θ� �Ƿ� ���_�� end
bool message_t::has_next()
{
	return _message->has_next();
}

//���� �Θ˷�Ƭ
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
