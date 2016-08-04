#pragma once
#include "message.h"
namespace dk
{
	namespace net
	{
		class reader
		{
		public:
			reader(void);
			~reader(void);

			bool get_message(const char* data,std::size_t size,message* p_msg);
		protected:
			//讀取 緩衝區
			std::vector<char> _datas;
			typedef std::vector<char>::iterator iterator_t;

			bool get_message(message* p_msg);

			message_data_ptr_t _data;

			message_data_ptr_t read_header();
			//已讀 body
			std::size_t _size;

			//尋找 第一個 分片頭 並且刪除 錯誤數據 (分片頭 之前的 數據)
			//返回 true 早到分片頭 false 未找到
			bool find_reader();
		};

	};
};