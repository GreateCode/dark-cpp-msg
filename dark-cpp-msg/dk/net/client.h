#pragma once
#include "reader_t.h"
#include "protocol_handler_t.h"
namespace dk
{
	namespace net
	{
		class client
			:public dark::net::tcp_client
		{
		public:
			client(const std::string& server,unsigned short port,std::size_t buf);
			~client(void);
		protected:
			virtual void closed();
			virtual void readed(const char* data,std::size_t bytes);
			virtual void writed(const boost::system::error_code& e,const char* data,std::size_t bytes);

			//�¼� ���{
			typedef boost::function<void()> b_func_closed_t;
			typedef boost::function<void(message_t*)> b_func_readed_t;
			typedef boost::function<void(std::size_t)> b_func_writed_t;
	
			b_func_closed_t _func_closed;
			b_func_readed_t _func_readed;
			b_func_writed_t _func_writed;

			reader_t _reader;

		public:
			inline void closed(b_func_closed_t func)
			{
				_func_closed = func;
			}
			inline void readed(b_func_readed_t func)
			{
				_func_readed = func;
			}
			inline void writed(b_func_writed_t func)
			{
				_func_writed = func;
			}
			void write_message(message_t& msg,error_t& e);

		protected:
			typedef boost::shared_ptr<protocol_handler_t> protocol_handler_ptr_t;
			boost::unordered_map<std::string,protocol_handler_ptr_t> _handlers;
		public:
			void register_protocol_handler(protocol_handler_ptr_t handler);
		};
	};
};

