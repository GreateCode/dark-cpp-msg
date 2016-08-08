#pragma once


namespace dk
{
	namespace net
	{
		namespace protocol
		{
			class file_handler;
			class FILE_HANDLER_API file_handler_t
				:public dk::net::protocol_handler_t
			{
			public:
				file_handler_t(void);
				~file_handler_t(void);

				virtual const std::string& get_hash()const ;
				virtual bool handler_message(SOCKET s,dk::net::message_t* p_msg);	
				
			protected:
				file_handler* _handler;
			};
		};
	};
};