#pragma once
#include "message_reader_t.h"
class client_handler
{
public:
	client_handler(void);
	~client_handler(void);

	dark::net::tcp_socket_t _socket;

	message_reader_t _reader;
};

typedef boost::shared_ptr<client_handler> client_handler_ptr_t;