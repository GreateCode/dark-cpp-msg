#pragma once
class client_handler
{
public:
	client_handler(void);
	~client_handler(void);

	dark::net::tcp_socket_t _socket;
};

typedef boost::shared_ptr<client_handler> client_handler_ptr_t;