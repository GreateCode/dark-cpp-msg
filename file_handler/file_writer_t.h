#pragma once

namespace dk
{
	namespace net
	{
		namespace protocol
		{

			class FILE_HANDLER_API file_writer_t
			{
			public:
				file_writer_t(std::size_t chunk,const std::string& file,std::size_t fid);
				~file_writer_t(void);

				virtual const std::string& get_hash()const;
				virtual bool get_message(std::size_t id,dk::net::message_t* p_msg);

			protected:
				std::ifstream _f;
				std::size_t _chunk;
				std::size_t _fid;
				std::string _name;

				std::size_t _size;
			};
		};
	};
};

