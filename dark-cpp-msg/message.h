#pragma once
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
	void id(std::size_t);
	void count(std::size_t n);

};

