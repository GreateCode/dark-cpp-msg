#pragma once
#include "reader_t.h"
#include "protocol_handler_t.h"
namespace dk
{
	namespace net
	{
		class client_handler
		{
		public:
			client_handler(void);
			~client_handler(void);

			dark::net::tcp_socket_t _socket;
			reader_t _reader;

			typedef boost::shared_ptr<protocol_handler_t> protocol_handler_ptr_t;
			boost::unordered_map<std::string,protocol_handler_ptr_t> _handlers;
			void register_protocol_handler(protocol_handler_ptr_t handler);
		};
		typedef boost::shared_ptr<client_handler> client_handler_ptr_t;
	};
};