#pragma once



namespace dk
{
	namespace net
	{
		namespace protocol
		{
			class TEXT_HANDLER_API text_handler_t
				:public dk::net::protocol_handler_t
			{
			public:
				text_handler_t(void);
				~text_handler_t(void);

				virtual const std::string& get_hash()const ;
				virtual bool handler_message(SOCKET s,dk::net::message_t* p_msg);

		
			};
		};
	};
};
