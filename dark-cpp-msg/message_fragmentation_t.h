#pragma once
#include "fragmentation.h"
class message_fragmentation;
class DARKCPPMSG_API message_fragmentation_t
{
public:
	message_fragmentation_t(void);
	~message_fragmentation_t(void);

	PMESSAGE_FRAGMENTATION_HEADER get_header();
	
	

	//Œ‘Èë”µ“þÁ÷
	void push(const char c);


	inline message_fragmentation* get_unpack()const
	{
		return _fragmentation;
	}
protected:
	void release();
	message_fragmentation* _fragmentation;
};

