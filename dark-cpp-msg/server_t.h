#pragma once
#include "message_t.h"

#include "public.h"

class server;


class DARKCPPMSG_API server_t
{
public:
	server_t(void);
	~server_t(void);

	//�͑��� �ɹ��B�� ���{
	typedef void (*s_func_accepted_t)(server_t*,SOCKET);
	//�͑��� ���� ���{
	typedef void (*s_func_closed_t)(server_t*,SOCKET);
	//���յ� �͑��� 1�l������Ϣ�� ���{
	typedef void (*s_func_readed_t)(server_t*,SOCKET,const char* data,std::size_t bytes);
	//�l�ͽo �͑��� 1�l������Ϣ�� ���{
	typedef void (*s_func_writed_t)(server_t*,SOCKET);

public:
	//��ָ���B�� �l�� ��Ϣ
	void write_message(SOCKET s,message_t msg,error_t& e);

	//���� ������
	void create(unsigned short port,std::size_t buf,error_t& e);

	//���� �������Ƿ� ������
	inline operator bool() const
	{
		return _server != NULL;
	}

	//�\�з��� ֱ�� ����ֹͣ �᷵�� 
	//(����ѽ�create ��t �О� δ���x)
	void run();

	//ֹͣ���� �Kጷŷ������YԴ
	void release();


protected:
	s_func_accepted_t _func_accepted;
	s_func_closed_t _func_closed;
	s_func_readed_t _func_readed;
	s_func_writed_t _func_writed;
public:
	//�O��/���� socket ̎�� ���{����
	//�O�Þ� NULL(Ĭ�J) ��̎�������¼�
	void accepted(s_func_accepted_t func);
	void closed(s_func_closed_t func);
	void readed(s_func_readed_t func);
	void writed(s_func_writed_t func);
	
	s_func_accepted_t accepted();
	s_func_closed_t closed();
	s_func_readed_t readed();
	s_func_writed_t writed();


	//���� socket ���P��Ϣ
	void get_remote_port(SOCKET s,unsigned short& port,error_t& e);
	void get_remote_address(SOCKET s,std::string& address,error_t& e);

private:
	server* _server;
};

