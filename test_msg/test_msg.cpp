// test_msg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../dark-cpp-msg/dk/net/tcp.h"

#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif

#define DARK_FILE_NODE_SIZE	1024 * 10

typedef struct _NET_DATA_HEADER_
{
	//指令
	std::size_t code;
	//文件id
	std::size_t id;
	//文件塊
	std::size_t order;
	//文件大小
	std::size_t size;
}NET_DATA_HEADER,*PNET_DATA_HEADER;

//上傳 文件
#define DARK_PROTOCOL_UPLOAD_FILE	1
//設置 文件 大小
#define DARK_PROTOCOL_SET_FILE_INFO	2
//設置 文件 數據
#define DARK_PROTOCOL_SET_FILE_BIN	3

typedef std::vector<std::string> strings_t;
typedef boost::shared_ptr<dk::net::message_t> message_ptr_t;

void test_write(dk::net::message_t& msg,const strings_t& strs);
void test_reader(dk::net::message_t& msg);
void test_file();
void test_file2();
void test_copy_file();
int _tmain(int argc, _TCHAR* argv[])
{
	strings_t strs;
	dk::net::message_t msg1,msg2;
	/**/
	strs.clear();
	strs.push_back("企鵝\n");
	strs.push_back("企鵝都是神經病\n");
	test_write(msg1,strs);
	/**/

	puts("****	writer one	****");
	strs.clear();
	strs.push_back("i work for cerberus\n");
	strs.push_back("cerberus it's an idea\n");
	test_write(msg1,strs);

	puts("****	writer two	****");
	strs.clear();
	strs.push_back("i'm a soldier\n");
	strs.push_back("i want join cerberus\n");
	test_write(msg2,strs);


	puts("****	reader	****");
	test_reader(msg1);
	

	puts("****	test file begin	****");
	test_copy_file();
	test_file();
	test_file2();
	puts("****	test file end	****");

	std::system("pause");
	return 0;
}
void test_copy_file()
{
	puts("test_copy_file");
	std::string name = "CDImage.ape";
	name = "ZGC_INS_7USP1(x64)2011V3.iso";
	name = "kate.jpg";

	std::string file = "d:/" + name;
	std::vector<message_ptr_t> msgs;
	std::ifstream inf(file,std::ios::in | std::ios::binary);
	std::ofstream outf("c-" + name,std::ios::out | std::ios::binary | std::ios::trunc);

	if(inf.is_open() && outf.is_open())
	{
		boost::shared_array<char> datas(new char[DARK_FILE_NODE_SIZE]);

		boost::progress_timer timer;
		while(!inf.eof())
		{
			inf.read(datas.get(),DARK_FILE_NODE_SIZE);
			std::size_t size = inf.gcount();
			if(size)
			{
				outf.write(datas.get() ,size);
			}
		}
	}
}
void test_file2()
{
	puts("test_file2");
	std::string name = "CDImage.ape";
	name = "ZGC_INS_7USP1(x64)2011V3.iso";
	name = "kate.jpg";

	std::string file = "d:/" + name;
	std::vector<message_ptr_t> msgs;
	std::ifstream inf(file,std::ios::in | std::ios::binary);
	std::ofstream outf("2-" + name,std::ios::out | std::ios::binary | std::ios::trunc);
	if(inf.is_open() && outf.is_open())
	{
		boost::shared_array<char> datas(new char[DARK_FILE_NODE_SIZE + sizeof(NET_DATA_HEADER)]);
		PNET_DATA_HEADER p_header = (PNET_DATA_HEADER)datas.get();
		char* p_body = (char*)datas.get() + sizeof(NET_DATA_HEADER);

		p_header->id = 1;
		p_header->order = 0;
		p_header->code = DARK_PROTOCOL_SET_FILE_BIN;

		boost::progress_timer timer;
		while(!inf.eof())
		{
			inf.read(p_body,DARK_FILE_NODE_SIZE);
			p_header->size = inf.gcount();
			
			if(p_header->size)
			{
				dk::net::writer_t writer;
				writer.push_data(datas.get(),sizeof(NET_DATA_HEADER) + p_header->size);
				message_ptr_t msg = boost::make_shared<dk::net::message_t>();
				writer.create_message(1,msg.get());
				

				std::size_t size = 0;
				dk::net::reader_t reader;

				dk::net::PMESSAGE_HEADER header = msg->get_header();
			
				dk::net::message_t m;
				const char* body = msg->get_body(&size);
				if(reader.get_message((const char*)header,5,&m))
				{
					puts("no");
					std::system("pause");
				}
				//if(reader.get_message(body,size,&m))
				if(reader.get_message(((const char*)header)+5,header->size + sizeof(dk::net::MESSAGE_HEADER)-5,&m))
				{
					const char* body = m.get_body(&size);

					outf.write(body + sizeof(NET_DATA_HEADER) ,size - sizeof(NET_DATA_HEADER));
				}

			}
			++p_header->order;
			++p_header->id;


		}
	}
}
void test_file()
{
	std::string name = "CDImage.ape";
	name = "ZGC_INS_7USP1(x64)2011V3.iso";
	name = "kate.jpg";

	std::string file = "d:/" + name;
	std::vector<message_ptr_t> msgs;
	std::ifstream inf(file,std::ios::in | std::ios::binary);
	if(inf.is_open())
	{
		puts("****	file write	****");
		boost::shared_array<char> datas(new char[DARK_FILE_NODE_SIZE + sizeof(NET_DATA_HEADER)]);
		PNET_DATA_HEADER p_header = (PNET_DATA_HEADER)datas.get();
		char* p_body = (char*)datas.get() + sizeof(NET_DATA_HEADER);

		p_header->id = 1;
		p_header->order = 0;
		p_header->code = DARK_PROTOCOL_SET_FILE_BIN;

		
		
		boost::progress_timer timer;
		while(!inf.eof())
		{
			inf.read(p_body,DARK_FILE_NODE_SIZE);
			p_header->size = inf.gcount();
			
			if(p_header->size)
			{
				dk::net::writer_t writer;

		
				writer.push_data(datas.get(),sizeof(NET_DATA_HEADER) + p_header->size);
		
				message_ptr_t msg = boost::make_shared<dk::net::message_t>();
				 
				writer.create_message(1,msg.get());
				msgs.push_back(msg);
			
			}
			++p_header->order;
			++p_header->id;
		}
	}

	std::ofstream outf(name,std::ios::out | std::ios::binary | std::ios::trunc);
	if(outf.is_open())
	{
		puts("****	file read	****");
		std::size_t size = 0;
		dk::net::reader_t reader;
		boost::progress_timer timer;
		BOOST_FOREACH(auto msg,msgs)
		{
			dk::net::PMESSAGE_HEADER header = msg->get_header();
			
			dk::net::message_t m;
			const char* body = msg->get_body(&size);
			if(reader.get_message((const char*)header,5,&m))
			{
				puts("no");
				std::system("pause");
			}
			//if(reader.get_message(body,size,&m))
			if(reader.get_message(((const char*)header)+5,header->size + sizeof(dk::net::MESSAGE_HEADER)-5,&m))
			{
				const char* body = m.get_body(&size);

				outf.write(body + sizeof(NET_DATA_HEADER) ,size - sizeof(NET_DATA_HEADER));
			}
		}
	}
}
void test_reader(dk::net::message_t& msg)
{
	dk::net::message_t m;
	dk::net::reader_t r;
	auto header = msg.get_header();
	char* ptr = (char*)header;
	if(r.get_message(ptr,1,&m))
	{
		puts("error");
		std::system("pause");
		return;
	}
	if(r.get_message(ptr+1,sizeof(dk::net::MESSAGE_HEADER)-1,&m))
	{
		puts("error");
		std::system("pause");
		return;
	}
	if(r.get_message(ptr + sizeof(dk::net::MESSAGE_HEADER),header->size,&m))
	{
		std::size_t size = 0;
		const char* str = m.get_body(&size);
		std::cout<<std::string(str,size)<<"\n";
	}

}
void test_write(dk::net::message_t& msg,const strings_t& strs)
{	
	dk::net::writer_t w;
	BOOST_FOREACH(const std::string& str,strs)
	{
		w.push_data(str.data(),str.size());
	}
	w.create_message(1,&msg);
	
	auto header = msg.get_header();

	std::ofstream outf("a.txt",std::ios::binary|std::ios::trunc|std::ios::out);
	outf.write((char*)header,header->size + sizeof(dk::net::MESSAGE_HEADER));
	outf.close();
	
	std::size_t size = 0;
	const char* ptr = msg.get_body(&size);
	std::cout<<std::string(ptr,size)<<"\n";
}