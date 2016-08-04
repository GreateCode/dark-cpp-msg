// test_fclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dk/net/tcp.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif
using namespace dk::net;

#include "../test-fserver/protocol.h"

#include <boost/program_options.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/progress.hpp>
#include <boost/timer.hpp>



void on_readed(client_t* client,message_t* p_msg);
void on_writed(client_t* client,std::size_t id);

#define DARK_FILE_NODE_SIZE	1024 * 8
std::ifstream g_inf;

boost::timer g_timer;
int _tmain(int argc, _TCHAR* argv[])
{
	boost::program_options::options_description opts("upload client");
	opts.add_options()
		("help,h","just a help info")
		("filename,f",
			boost::program_options::value<std::string>()//設置 參數值型別
				->default_value("d:/CDImage.ape")	//默認值
				//->default_value("d:/ZGC_INS_7USP1(x64)2011V3.iso")	//默認值
				,
			"upload file");
	boost::program_options::variables_map params;
	boost::program_options::store(boost::program_options::parse_command_line(argc,argv,opts),params);

	if(params.count("help") || !params.count("filename"))
	{
		std::cout<<opts<<"\n";
		std::system("pause");
		return 0;
	}
	std::string file = params["filename"].as<std::string>();

	g_inf.open(file,std::ios::in | std::ios::binary);
	g_inf.seekg(0,std::ios::end);
	DWORD size = g_inf.tellg();
	NET_DATA_HEADER header;
	header.code = DARK_PROTOCOL_UPLOAD_FILE;
	header.size = size;

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

	client.readed(on_readed);
	client.writed(on_writed);


	//發送 文件
	{
		writer_t writer;

		
		writer.push_data((char*)&header,sizeof(header));
		
		message_t msg;
		writer.create_message(client.new_id(),&msg);

		client.write_message(msg,e);
	}

	//設置 事件處理 回調
	client.run();

	std::system("pause");
	return 0;
}


void on_readed(client_t* client,message_t* p_msg)
{
	std::size_t size = 0;
	const char* buf = p_msg->get_body(&size);
	if(size < sizeof(NET_DATA_HEADER))
	{
		return;
	}
	PNET_DATA_HEADER header = (PNET_DATA_HEADER)buf;
	error_t e;

	switch(header->code)
	{
	case DARK_PROTOCOL_UPLOAD_FILE:
		{
			boost::shared_array<char> datas(new char[DARK_FILE_NODE_SIZE + sizeof(NET_DATA_HEADER)]);
			PNET_DATA_HEADER p_header = (PNET_DATA_HEADER)datas.get();
			char* p_body = (char*)datas.get() + sizeof(NET_DATA_HEADER);

			p_header->id = header->id;
			p_header->code = DARK_PROTOCOL_SET_FILE_BIN;

			g_inf.seekg(0,std::ios::beg);
			std::size_t sum = 0;
			g_timer.restart();
			while(!g_inf.eof())
			{
				p_header->pos = sum;
				g_inf.read(p_body,DARK_FILE_NODE_SIZE);
				p_header->size = g_inf.gcount();
				sum += p_header->size;
				if(p_header->size)
				{
					writer_t writer;

		
					writer.push_data(datas.get(),sizeof(NET_DATA_HEADER) + p_header->size);
		
					message_t msg;
					writer.create_message(client->new_id(),&msg);
					client->write_message(msg,e);
				}
			}
		}
		break;
	case DARK_PROTOCOL_SET_FILE_BIN:
		std::cout<<g_timer.elapsed()<<"\n";
		client->stop();
		break;
	}
}
void on_writed(client_t* client,std::size_t id)
{
}