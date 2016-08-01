#include "StdAfx.h"
#include "client.h"

using namespace dark::net;
client::client(const std::string& server,unsigned short port,std::size_t buf,error_t& e)
	:tcp_client(server,port,buf,e)
{
}


client::~client(void)
{
}

void client::closed()
{
	if(_func_closed)
	{
		_func_closed();
	}
}

void client::readed(const char* data,std::size_t bytes)
{
	message_t msg;
	if(_reader.get_message(data,bytes,&msg))
	{
		if(_func_readed)
		{
			_func_readed(&msg);
		}
	}
}
	
void client::writed(const boost::system::error_code& e,const char* data,std::size_t bytes)
{
	//數據傳輸 錯誤 斷開連接
	if(e)
	{
		//關閉 回調
		if(_func_closed)
		{
			_func_closed();
		}

		//關閉連接
		stop();
	}
}
void client::write_message(message_t& msg,error_t& e)
{
	if(msg.begin())
	{
		//組合消息
		std::list<char> tmp;
		do
		{
			message_fragmentation_t* fragmentation = msg.get();
			PMESSAGE_FRAGMENTATION_HEADER header = fragmentation->get_header();
			//寫入 header
			for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
			{
				tmp.push_back(((char*)header)[i]);
			}
			
			boost::scoped_array<char> buf(new char[header->size]);
			std::size_t size = fragmentation->clone_binary(buf.get());
			//寫入 body
			for(std::size_t i=0;i<size;++i)
			{
				tmp.push_back(buf[i]);
			}
		}while(msg.next());


		//發送 消息
		buffer_ptr_t buffer = boost::make_shared<std::vector<char>>(tmp.size(),0);
		std::copy(tmp.begin(),tmp.end(),buffer->begin());
		write(buffer);
	}
}