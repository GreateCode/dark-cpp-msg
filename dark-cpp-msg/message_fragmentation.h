#pragma once

//��Ϣ��Ƭ �^
typedef struct _MESSAGE_FRAGMENTATION_HEADER_
{
	//��Ϣ��Ƭ�^ ��ӛ �̶��� ^
	char falg[4];

	//��Ϣ Ψһ���R��
	DWORD id;

	//��Ƭ ����
	WORD order;
	//��Ƭ ���� ��С(������ ��Ƭ�^)
	WORD size;

	//��Ƭ����
	DWORD count;
}MESSAGE_FRAGMENTATION_HEADER,*PMESSAGE_FRAGMENTATION_HEADER;

//��Ϣ��Ƭ
class message_fragmentation
{
public:
	message_fragmentation();
	~message_fragmentation();

	MESSAGE_FRAGMENTATION_HEADER _header;
	std::list<char> _body;
};
typedef boost::shared_ptr<message_fragmentation> message_fragmentation_ptr_t;
