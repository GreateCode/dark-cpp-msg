#pragma once
#include "public.h"
namespace dk
{
	namespace net
	{
		typedef dark::net::buffer_ptr_t message_data_ptr_t;

		class message
		{
		public:
			message(void);
			~message(void);

		public:
			message_data_ptr_t _data;

		public:
			PMESSAGE_HEADER get_header()const;
			const char* get_body(std::size_t* size);
		};
	};
};

