#pragma once
#include "message_fragmentation_t.h"
class message;
class DARKCPPMSG_API message_t
{
public:
	message_t(void);
	~message_t(void);

	//���ط�Ƭ����
	std::size_t size()const;
	
	//������Ϣ�Ƿ���
	bool empty()const;
	

	//��Ƭ�Θ� �Ƅӵ���һ��λ��
	//���� �Ƿ� δ�_�� end (�� _nodes ��Օr)
	bool begin();
	
	//��Ƭ�Θ� ����  
	//���� �Ƅ��� �Ƿ� δ�_�� end
	bool next();

	//�����Θ� �Ƿ� ���_�� end
	bool has_next();

	//���� �Θ˷�Ƭ
	message_fragmentation_t* get();

	
	inline operator bool()const
	{
		return _message != NULL;
	}
	inline message* get_unpack()const
	{
		return _message;
	}
	void create();
	void release();

	message* swap(message* ptr);
protected:
	message* _message;

};

