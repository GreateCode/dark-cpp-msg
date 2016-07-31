#pragma once
#include "message_t.h"
#include "message.h"
#include "message_fragmentation.h"

#define DARK_MESSAGE_FRAGMENTATION_MIN	10
#define DARK_MESSAGE_FRAGMENTATION_MAX	0xFFF0

class message_writer
{
public:
	//size ���Ƭ ��С ��ֵֻ ���� ���� ���Hֵ ���ܲ�һ��
	message_writer(std::size_t size);
	~message_writer(void);

protected:
	std::size_t _size;

	//������
	std::deque<char> _datas;

	//��Ϣ
	message* _message;

	//��ǰ��Ƭ ��Ƭ��С order
	message_fragmentation_ptr_t _fragmentation;
	std::size_t _fragmentation_order;
public:
	//���딵����
	void push_data(const char* data,std::size_t size);

	//���� ��Ϣ
	//id ����Ϣ ���R��
	void create_message(DWORD id,message_t* p_msg);
};

