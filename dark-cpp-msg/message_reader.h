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
	typedef std::deque<char>::iterator iterator_t;

	//���x��� ��Ƭ
	std::map<WORD/*order*/,message_fragmentation_ptr_t> _fragmentations;
	//���� ��Ϣ�^
	message_fragmentation_ptr_t _fragmentation_header;

	//���� ��һ�� ��Ƭ�^ �K�҄h�� �e�`���� (��Ƭ�^ ֮ǰ�� ����)
	//���� true �絽��Ƭ�^ false δ�ҵ�
	bool find_reader();

	//��ǰ��Ƭ
	message_fragmentation_ptr_t _fragmentation;
	bool get_message(message_t* p_msg);
	bool create_message(message_t* p_msg);

	void reset();
	message_fragmentation_ptr_t read_header();
};

