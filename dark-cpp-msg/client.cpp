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
	//������ݔ �e�` ���_�B��
	if(e)
	{
		//�P�] ���{
		if(_func_closed)
		{
			_func_closed();
		}

		//�P�]�B��
		stop();
	}
}
void client::write_message(message_t& msg,error_t& e)
{
	if(msg.begin())
	{
		//�M����Ϣ
		std::list<char> tmp;
		do
		{
			message_fragmentation_t* fragmentation = msg.get();
			PMESSAGE_FRAGMENTATION_HEADER header = fragmentation->get_header();
			//���� header
			for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
			{
				tmp.push_back(((char*)header)[i]);
			}
			
			boost::scoped_array<char> buf(new char[header->size]);
			std::size_t size = fragmentation->clone_binary(buf.get());
			//���� body
			for(std::size_t i=0;i<size;++i)
			{
				tmp.push_back(buf[i]);
			}
		}while(msg.next());


		//�l�� ��Ϣ
		buffer_ptr_t buffer = boost::make_shared<std::vector<char>>(tmp.size(),0);
		std::copy(tmp.begin(),tmp.end(),buffer->begin());
		write(buffer);
	}
}