// test_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../dark-cpp-msg/dk/net/tcp.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif

using namespace dk::net;

void on_closed(client_t* client);
void on_readed(client_t* client,message_t* p_msg);
void on_writed(client_t* client,std::size_t id);
int _tmain(int argc, _TCHAR* argv[])
{
	
	//連接服務器
	std::string server = "127.0.0.1";
	unsigned short port = 1102;
	error_t e;
	client_t client;
	client.connect(server,port,512,e);
	if(e)
	{
		std::cout<<e.value<<"("<<e.emsg<<")\n";
		std::system("pause");
		return 0;
	}

	//設置 事件處理 回調
	client.closed(on_closed);
	client.readed(on_readed);
	client.writed(on_writed);

	//運行 異步 服務
	client.run();

	//std::system("pause");
	return 0;
}

void on_closed(client_t* client)
{
	puts("close");
}
void on_readed(client_t* client,message_t* p_msg)
{
	std::size_t size = 0;
	const char* ptr = p_msg->get_body(&size);
	std::string str(ptr,size);
	
	std::cout<<"recv : "<<str<<"\n";

	if(str == "cerberus it's an idea")
	{
		error_t e;
		/*
		{
			writer_t writer;

			std::string str = "i kill you";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}
		*/
		{
			writer_t writer;

			std::string str = "i'm a soldier";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}

		{
			writer_t writer;

			std::string str = "i want join cerberus";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}
	}
	else if(str == "you are cerberus soldier now")
	{
		client->stop();
	}
}
void on_writed(client_t* client,std::size_t id)
{

}