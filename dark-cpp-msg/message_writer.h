#pragma once
class message_writer
{
public:
	message_writer(void);
	~message_writer(void);

protected:
	//Œ‘ÈëÁ÷
	std::deque<char> _datas;
public:
	void push_data(const char* data,DWORD size);
};

