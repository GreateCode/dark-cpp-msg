#pragma once
#include "message_t.h"
#ifndef DK_PROTOCOL_HASH_SIZE
#define DK_PROTOCOL_HASH_SIZE	32
#endif
namespace dk
{
	namespace net
	{
		class DARKCPPMSG_API protocol_handler_t
		{
		public:
			protocol_handler_t(void);
			~protocol_handler_t(void);
		public:
			//32 ×Ö¹µÄ md5×Ö·û´®
			virtual const std::string& get_hash()const = 0;
			virtual bool handler_message(SOCKET s,message_t* p_msg)=0;
		};
		
	};
}
