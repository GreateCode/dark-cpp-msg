// test_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../dark-cpp-msg/dark-cpp-msg.h"
#pragma comment(lib,"../debug/dark-cpp-msg.lib")

#define DARK_TEST_MSG_FRAGMENTATION_SIZE	1024

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
	std::cout<<"recv : "<<str<<"\n";

	if(str == "cerberus it's an idea")
	{
		error_t e;
		{
			message_writer_t writer(DARK_TEST_MSG_FRAGMENTATION_SIZE);

			std::string str = "i'm a soldier";
			writer.push_data(str.data(),str.size());

			message_t msg;
			writer.create_message(client->new_id(),&msg);

			client->write_message(msg,e);
		}

		{
			message_writer_t writer(DARK_TEST_MSG_FRAGMENTATION_SIZE);

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