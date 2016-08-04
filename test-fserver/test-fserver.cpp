// test-fserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../dark-cpp-msg/dk/net/tcp.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif
using namespace dk::net;


#include "protocol.h"
#include "upload_file.h"

typedef boost::shared_array<char> datas_t;
typedef std::pair<std::size_t,datas_t> buffer_t;

void on_readed(server_t* server,SOCKET s,message_t* p_msg);

int _tmain(int argc, _TCHAR* argv[])
{
	server_t server;
	error_t e;
	//設置 listen 端口 recv 緩衝區
	server.create(1102,1024*5,e);
	if(e)
	{
		std::cout<<e.value<<"("<<e.emsg<<")\n";
		std::system("pause");
		return 0;
	}
	puts("listen at 1102");

	server.readed(on_readed);
	server.run();

	return 0;
}

void on_readed(server_t* server,SOCKET s,message_t* p_msg)
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
			header->id = upload_file::get_mutable_instance().new_file(header->size);
			
			//回傳 等待 文件數據
			{
				writer_t writer;
				
		
				writer.push_data((char*)header,sizeof(NET_DATA_HEADER));
		
				message_t msg;
				writer.create_message(server->new_id(),&msg);

				server->write_message(s,msg,e);
			}
		}
		break;
	case DARK_PROTOCOL_SET_FILE_INFO:
		break;
	case DARK_PROTOCOL_SET_FILE_BIN:
		{
			if(upload_file::get_mutable_instance().write_file(header->id,
				header->pos,
				buf + sizeof(NET_DATA_HEADER),
				header->size)
				)
			{
				writer_t writer;
				
		
				writer.push_data((char*)header,sizeof(NET_DATA_HEADER));
		
				message_t msg;
				writer.create_message(server->new_id(),&msg);

				server->write_message(s,msg,e);
			}
		}
		break;
	}
}
