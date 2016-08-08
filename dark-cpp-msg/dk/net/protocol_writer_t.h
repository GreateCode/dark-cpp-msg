#pragma once
#include "message_t.h"
#ifndef DK_PROTOCOL_HASH_SIZE
#define DK_PROTOCOL_HASH_SIZE	32
#endif
namespace dk
{
	namespace net
	{
		class DARKCPPMSG_API protocol_writer_t
		{
		public:
			protocol_writer_t(void);
			~protocol_writer_t(void);

			virtual const std::string& get_hash() const= 0;
			virtual bool get_message(std::size_t id,message_t* p_msg)=0;
		};
	};
};
