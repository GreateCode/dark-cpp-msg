// test_msg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dark-cpp-msg.h"
#pragma comment(lib,"../debug/dark-cpp-msg.lib")

#include <vector>
typedef std::vector<char> datas_t;
void test_write(datas_t& datas);
void test_write2(datas_t& datas);
void test_read(datas_t& datas);

int _tmain(int argc, _TCHAR* argv[])
{
	datas_t datas;
	puts("*******	one	*****");
	test_write(datas);
	
	puts("*******	two	*****");
	datas.clear();
	test_write2(datas);

	test_read(datas);

	std::system("pause");
	return 0;
}

void test_read(datas_t& datas)
{
	message_reader_t reader;
	message_t msg;

	if(reader.get_message(datas.data(),datas.size(),&msg))
	{
		do
		{
			if(msg.begin())
			{
				std::cout<<"*************\n";
				do
				{
					char buf[1024] = {0};
					message_fragmentation_t* fragmentation = msg.get();
					auto header = fragmentation->get_header();
					std::size_t size = fragmentation->clone(buf);
					std::string str(buf,size);

					std::cout<<"order = "<<header->order<<"	"<<str<<"\n";
				}while(msg.next());
			}
		}
		while(reader.get_message(NULL,0,&msg));
	}
}
void test_write2(datas_t& datas)
{
	message_writer_t writer(10);

	std::string str = "123^456\\789\\]0";
	writer.push_data(str.data(),str.size());
	str = "abc\\[defg";
	writer.push_data(str.data(),str.size());
	message_t msg;
	writer.create_message(1,&msg);

	if(msg.begin())
	{
		char buf[1024] = {0};
		do
		{
			message_fragmentation_t* fragmentation = msg.get();
			auto header = fragmentation->get_header();
			std::size_t size = fragmentation->clone_binary(buf);
			std::string str(buf,size);

			std::cout<<"order = "<<header->order<<"	"<<str<<"\n";


			char* ptr = (char*)header;
			for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
			{
				datas.push_back(ptr[i]);
			}
			for(std::size_t i=0;i<size;++i)
			{
				datas.push_back(buf[i]);
			}
		}while(msg.next());
	}
}
void test_write(datas_t& datas)
{
	message_writer_t writer(10);

	std::string str = "123^456\\789\\]0";
	writer.push_data(str.data(),str.size());
	str = "abc\\[defg";
	writer.push_data(str.data(),str.size());
	message_t msg;
	writer.create_message(1,&msg);

	if(msg.begin())
	{
		char buf[1024] = {0};
		do
		{
			message_fragmentation_t* fragmentation = msg.get();
			auto header = fragmentation->get_header();
			std::size_t size = fragmentation->clone(buf);
			std::string str(buf,size);

			std::cout<<"order = "<<header->order<<"	"<<str<<"\n";


			char* ptr = (char*)header;
			for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
			{
				datas.push_back(ptr[i]);
			}
			for(std::size_t i=0;i<size;++i)
			{
				datas.push_back(buf[i]);
			}
		}while(msg.next());
	}
}