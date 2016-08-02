#pragma once
#include "error_t.h"
#include "message_t.h"
class client;
class DARKCPPMSG_API client_t
{
public:
	client_t();
	~client_t(void);
private:
	client_t(const client_t& copy);
	client_t operator=(const client_t& copy);
public:
	void connect(const std::string& server,unsigned short port,std::size_t buf,error_t& e);


	//返回 是否連接服務器成功
	inline operator bool() const
	{
		return _client != NULL;
	}

	//運行異步 socket 服務 直到 服務停止 後返回 
	//(必須已經connect成功 否則 行為 未定義)
	void run();

	//停止服務
	void stop();
protected:
	void release();
public:
	//斷開服務器 回調
	typedef void (*s_func_closed_t)(client_t*);

	//接收到 客戶端 1條完整消息後 回調
	typedef void (*s_func_readed_t)(client_t*,message_t*);

	//發送 1條完整消息後 回調
	typedef void (*s_func_writed_t)(client_t*,std::size_t);
protected:
	s_func_closed_t _func_closed;
	s_func_readed_t _func_readed;
	s_func_writed_t _func_writed;

public:
	//設置/返回 socket 處理 回調函數
	//設置為 NULL(默認) 不處理相應事件
	void closed(s_func_closed_t func);
	void readed(s_func_readed_t func);
	void writed(s_func_writed_t func);
	
	s_func_closed_t closed();
	s_func_readed_t readed();
	s_func_writed_t writed();

	//向服務器 發送 消息
	void write_message(message_t& msg,error_t& e);

protected:
	std::size_t _id;
public:
	inline std::size_t new_id()
	{
		return ++_id;
	}
protected:
	client* _client;
};

