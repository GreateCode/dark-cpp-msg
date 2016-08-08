// test_handler_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dk/net/tcp.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif

#include "../text_handler/handler.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/text_handler-mdd.lib")
#else
#pragma comment(lib,"../release/text_handler-md.lib")
#endif

#include "../file_handler/handler.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/file_handler-mdd.lib")
#else
#pragma comment(lib,"../release/file_handler-md.lib")
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

	//註冊 處理器
	client.register_protocol_handler(new dk::net::protocol::text_handler_t,NULL);
	client.register_protocol_handler(new dk::net::protocol::file_handler_t,NULL);

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
	std::string cmd(ptr,size);

	if(cmd == "who are you")
	{
		error_t e;
		{
			std::string str = "i'm a soldier";
			dk::net::protocol::text_writer_t writer(str.data(),str.size());
		
			message_t msg;
			writer.get_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}
		
		{
			std::string str = "i want join cerberus";
			dk::net::protocol::text_writer_t writer(str.data(),str.size());
		
			message_t msg;
			writer.get_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}

		{
			writer_t writer;

			std::string str = "can i join cerberus";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}
	}
	else if(cmd == "give me a certificate")
	{
		static DWORD fid = 1;
		dk::net::protocol::file_writer_t writer(1024 * 8,std::string("d:/kate.jpg"),fid++);

		error_t e;
		dk::net::message_t msg;
		while(writer.get_message(client->new_id(),&msg))
		{
			client->write_message(msg,e);
		}

		{
			writer_t writer;

			std::string str = "give me a idea";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);
		

			client->write_message(msg,e);
		}
	}
}
void on_writed(client_t* client,std::size_t id)
{
}