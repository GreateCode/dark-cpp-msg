// test_server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dark-cpp-msg.h"
#ifndef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg.lib")
#endif

#define DARK_TEST_MSG_FRAGMENTATION_SIZE	1024

void on_accept(server_t* server,SOCKET s);
void on_close(server_t* server,SOCKET s);
void on_recv(server_t* server,SOCKET s,message_t* p_msg);
void on_send(server_t* server,SOCKET s,std::size_t id);
int _tmain(int argc, _TCHAR* argv[])
{
	server_t server;
	error_t e;
	//設置 listen 端口 recv 緩衝區
	server.create(1102,10240,e);
	if(e)
	{
		std::cout<<e.value<<"("<<e.emsg<<")\n";
		std::system("pause");
		return 0;
	}
	puts("listen at 1102");

	//設置 事件處理 回調
	server.accepted(on_accept);
	server.closed(on_close);
	server.readed(on_recv);
	server.writed(on_send);
	
	server.run();

	return 0;
}

void on_accept(server_t* server,SOCKET s)
{
	std::string address;
	unsigned short port = 0;
	error_t e;
	server->get_remote_address(s,address,e);
	server->get_remote_port(s,port,e);
	std::cout<<"one in	"<<s<<"	("<<address<<":"<<port<<")"<<"\n";


	//send first msg
	{
		message_writer_t writer(DARK_TEST_MSG_FRAGMENTATION_SIZE);

		std::string str = "welcome to cerberus server";
		writer.push_data(str.data(),str.size());

		message_t msg;
		writer.create_message(server->new_id(),&msg);

		server->write_message(s,msg,e);
		if(e)
		{
			std::cout<<"write welcome emsg "<<s<<e.emsg<<"\n";
		}
	}
	//msg 2
	{
		message_writer_t writer(DARK_TEST_MSG_FRAGMENTATION_SIZE);

		std::string str = "cerberus it's an idea";
		writer.push_data(str.data(),str.size());

		message_t msg;
		writer.create_message(server->new_id(),&msg);

		server->write_message(s,msg,e);

		if(e)
		{
			std::cout<<"write cerberus emsg "<<s<<e.emsg<<"\n";
		}
	}
}
void on_close(server_t* server,SOCKET s)
{
	std::string address;
	unsigned short port = 0;
	error_t e;
	server->get_remote_address(s,address,e);
	server->get_remote_port(s,port,e);
	std::cout<<"one out	"<<s<<"	("<<address<<":"<<port<<")"<<"\n";

}
void on_recv(server_t* server,SOCKET s,message_t* p_msg)
{
	std::string str;
	if(p_msg->begin())
	{

		do
		{
			message_fragmentation_t* fragmentation = p_msg->get();
			
			PMESSAGE_FRAGMENTATION_HEADER header = fragmentation->get_header();
			char* buf = new char[header->size];
			{
				std::size_t size = fragmentation->clone(buf);
				str += std::string(buf,size);
			}
			delete buf;
		}while(p_msg->next());
	}
	std::cout<<"recv ("<<s<<") : "<<str<<"\n";
	
	if(str == "i want join cerberus")
	{
		message_writer_t writer(DARK_TEST_MSG_FRAGMENTATION_SIZE);

		std::string str = "you are cerberus soldier now";
		writer.push_data(str.data(),str.size());

		message_t msg;
		writer.create_message(server->new_id(),&msg);

		error_t e;
		server->write_message(s,msg,e);

		if(e)
		{
			std::cout<<"write soldier emsg "<<s<<e.emsg<<"\n";
		}
	}
	else if(str == "i kill you")
	{
		server->stop();
	}
}
void on_send(server_t* server,SOCKET s,std::size_t id)
{

}
