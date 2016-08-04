#pragma once
#include "message.h"
namespace dk
{
	namespace net
	{
		class writer
		{
		public:
			writer(void);
			~writer(void);

			//壓入數據流
			void push_data(const char* data,std::size_t size);

			//創建 消息
			//id 為消息 標識符
			void create_message(std::size_t id,message* p_msg);

		protected:
			typedef boost::shared_array<char> buffer_ptr_t;
			typedef std::pair<std::size_t,buffer_ptr_t> buffer_t;
			std::list<buffer_t> _buffers;
		};
	};
};
