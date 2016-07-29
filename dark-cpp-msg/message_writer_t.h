#pragma once
#include "message_t.h"
class message_writer;
class DARKCPPMSG_API message_writer_t
{
public:
	message_writer_t(void);
	~message_writer_t(void);

	//���딵����
	void push_data(const char* data,std::size_t size);

	//���� ��Ϣ
	//id ����Ϣ ���R��
	//size ���Ƭ ��С ��ֵֻ ���� ���� ���Hֵ ���ܲ�һ��
	void create_message(DWORD id,WORD size,message_t* p_msg);

	void release();
private:
	message_writer* _writer;
};

