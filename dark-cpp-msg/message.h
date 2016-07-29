#pragma once
class message
{
public:
	message(void);
	~message(void);

protected:
	//消息 唯一標識符
	std::size_t _id;
	//分片數量
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

