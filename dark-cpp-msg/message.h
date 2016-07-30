#pragma once
#include "message_fragmentation_t.h"
typedef boost::shared_ptr<message_fragmentation_t> message_fragmentation_ptr_t;
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
	void id(std::size_t n);
	void count(std::size_t n);

	inline void insert(message_fragmentation_ptr_t fragmentation)
	{
		_fragmentations.insert(
			std::make_pair(fragmentation->get_header()->order,fragmentation)
			);
	}
protected:
	//消息 分片 集合
	std::map<WORD/*order*/,message_fragmentation_ptr_t/*fragmentation*/> _fragmentations;

	typedef std::map<WORD/*order*/,message_fragmentation_ptr_t/*fragmentation*/>::iterator iterator_t;
	//分片游標
	iterator_t _iter;
public:
	//返回分片數量
	inline std::size_t size()const
	{
		return _fragmentations.size();
	}
	//返回消息是否為空
	inline bool empty()const
	{
		return _fragmentations.empty();
	}

	//分片游標 移動到第一個位置
	//返回 是否 未達到 end (如 _nodes 為空時)
	inline bool begin()
	{
		_iter = _fragmentations.begin();
		return _iter !=  _fragmentations.end();
	}
	//分片游標 下移  
	//返回 移動後 是否 未達到 end
	inline bool next()
	{
		++_iter;
		return _iter != _fragmentations.end();
	}

	//返回游標 是否 為達到 end
	inline bool has_next()
	{
		return _iter != _fragmentations.end();
	}

	//返回 游標分片
	inline message_fragmentation_t* get()
	{
		return _iter->second.get();
	}
};

