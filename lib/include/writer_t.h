#pragma once
#include "message_t.h"
namespace dk
{
	namespace net
	{
		class writer;
		class DARKCPPMSG_API writer_t
		{
		public:
			writer_t(void);
			~writer_t(void);

			//壓入數據流
			void push_data(const char* data,std::size_t size);

			//創建 消息
			//id 為消息 標識符
			void create_message(std::size_t id,message_t* p_msg);

		protected:
			writer* _writer;
		};
	};
};

