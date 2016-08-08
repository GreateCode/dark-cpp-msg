#pragma once
#include "file.h"
namespace dk
{
	namespace net
	{
		namespace protocol
		{
			class file_handler
			{
			public:
				file_handler(void);
				~file_handler(void);

				
				bool handler_message(SOCKET s,dk::net::message_t* p_msg);
			protected:
				boost::unordered_map<std::size_t,file_ptr_t> _fs;
				file_ptr_t get_file(std::size_t id);
			};
		};
	};
};
