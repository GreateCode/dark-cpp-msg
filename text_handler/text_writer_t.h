#pragma once

namespace dk
{
	namespace net
	{
		namespace protocol
		{
			class TEXT_HANDLER_API text_writer_t
			{
			public:
				text_writer_t(const char* str,std::size_t size);
				~text_writer_t(void);

			public:
				virtual const std::string& get_hash()const;
				virtual bool get_message(std::size_t id,dk::net::message_t* p_msg);

			private:
				dk::net::writer_t _writer;
				bool _ok;
			};
		};
	};
};
