#pragma once
#include "message_t.h"
namespace dk
{
	namespace net
	{
		class writer;
		class DARKCPPMSG_API writer_t
		{
		public:
			writer_t(void);
			~writer_t(void);

			//���딵����
			void push_data(const char* data,std::size_t size);

			//���� ��Ϣ
			//id ����Ϣ ���R��
			void create_message(std::size_t id,message_t* p_msg);

		protected:
			writer* _writer;
		};
	};
};

