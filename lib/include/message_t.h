#pragma once
#include "public.h"

namespace dk
{
	namespace net
	{
		class message;
		class DARKCPPMSG_API message_t
		{
		public:
			message_t(void);
			~message_t(void);


			PMESSAGE_HEADER get_header()const;
			const char* get_body(std::size_t* size);

		public:
			inline message* get_unpack()const
			{
				return _message;
			}
		protected:
			message* _message;
		};

	};
};