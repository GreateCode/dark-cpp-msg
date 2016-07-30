#pragma once
#include "message_fragmentation_t.h"
typedef boost::shared_ptr<message_fragmentation_t> message_fragmentation_ptr_t;
class message
{
public:
	message(void);
	~message(void);

protected:
	//��Ϣ Ψһ���R��
	std::size_t _id;
	//��Ƭ����
	std::size_t _count;
public:
	inline std::size_t id()const
	{
		return _id;
	}
	inline std::size_t count()const
	{
		return _count;
	}
	void id(std::size_t n);
	void count(std::size_t n);

	inline void insert(message_fragmentation_ptr_t fragmentation)
	{
		_fragmentations.insert(
			std::make_pair(fragmentation->get_header()->order,fragmentation)
			);
	}
protected:
	//��Ϣ ��Ƭ ����
	std::map<WORD/*order*/,message_fragmentation_ptr_t/*fragmentation*/> _fragmentations;

	typedef std::map<WORD/*order*/,message_fragmentation_ptr_t/*fragmentation*/>::iterator iterator_t;
	//��Ƭ�Θ�
	iterator_t _iter;
public:
	//���ط�Ƭ����
	inline std::size_t size()const
	{
		return _fragmentations.size();
	}
	//������Ϣ�Ƿ���
	inline bool empty()const
	{
		return _fragmentations.empty();
	}

	//��Ƭ�Θ� �Ƅӵ���һ��λ��
	//���� �Ƿ� δ�_�� end (�� _nodes ��Օr)
	inline bool begin()
	{
		_iter = _fragmentations.begin();
		return _iter !=  _fragmentations.end();
	}
	//��Ƭ�Θ� ����  
	//���� �Ƅ��� �Ƿ� δ�_�� end
	inline bool next()
	{
		++_iter;
		return _iter != _fragmentations.end();
	}

	//�����Θ� �Ƿ� ���_�� end
	inline bool has_next()
	{
		return _iter != _fragmentations.end();
	}

	//���� �Θ˷�Ƭ
	inline message_fragmentation_t* get()
	{
		return _iter->second.get();
	}
};

