#pragma once
#include "message_t.h"
class message_writer;
class DARKCPPMSG_API message_writer_t
{
public:
	//size ���Ƭ ��С ��ֵֻ ���� ���� ���Hֵ ���ܲ�һ��
	message_writer_t(std::size_t size);
	~message_writer_t(void);

	//���딵����
	void push_data(const char* data,std::size_t size);

	//���� ��Ϣ
	//id ����Ϣ ���R��
	void create_message(DWORD id,message_t* p_msg);

protected:
	std::size_t _size;
	void release();
	message_writer* _writer;
};

