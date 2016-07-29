// test_server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dark-cpp-msg.h"
#pragma comment(lib,"../debug/dark-cpp-msg.lib")

void on_accept(server_t* server,SOCKET s);
void on_cloe(server_t* server,SOCKET s);

int _tmain(int argc, _TCHAR* argv[])
{
	server_t server;
	error_t e;
	//設置 listen 端口 recv 緩衝區
	server.create(1102,10240,e);
	if(e)
	{
		std::cout<<e.value<<"("<<e.emsg<<")\n";
		return 0;
	}
	puts("listen at 1102");

	//設置 事件處理 回調
	server.accepted(on_accept);
	server.closed(on_cloe);
	

	
	server.run();

	server.release();
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
}
void on_cloe(server_t* server,SOCKET s)
{
	std::string address;
	unsigned short port = 0;
	error_t e;
	server->get_remote_address(s,address,e);
	server->get_remote_port(s,port,e);
	std::cout<<"one out	"<<s<<"	("<<address<<":"<<port<<")"<<"\n";

}