#pragma once
#include "message_t.h"
namespace dk
{
	namespace net
	{
		class reader;
		class DARKCPPMSG_API reader_t
		{
		public:
			reader_t(void);
			~reader_t(void);

			bool get_message(const char* data,std::size_t size,message_t* p_msg);
		
		protected:
			reader* _reader;
		};
	};
};
