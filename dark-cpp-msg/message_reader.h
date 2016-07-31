#pragma once
#include "message_t.h"
#include "message.h"
class message_reader
{
public:
	message_reader(void);
	~message_reader(void);

	//���딵��������Ϣ
	//��� �ɹ����յ�һ�l������Ϣ ���� ture �K����Ϣ���ص�p_msg
	//��t ���� false
	bool get_message(const char* data,std::size_t size,message_t* p_msg);

protected:
	//�xȡ ���n�^
	std::deque<char> _datas;

	//��ǰ��Ƭ
	message_fragmentation_ptr_t _fragmentation;

	message_fragmentation_ptr_t read_header(const char* data,std::size_t size,std::size_t pos);
};

