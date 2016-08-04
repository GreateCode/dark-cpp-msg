#pragma once
#include "public.h"
#include "message_t.h"
namespace dk
{
	namespace net
	{
		class client;
		class DARKCPPMSG_API client_t
		{
		public:
			client_t(void);
			~client_t(void);
		public:
			inline client* get_unpack()const
			{
				return _client;
			}
		protected:
			client* _client;

		public:
			void connect(const std::string& server,unsigned short port,std::size_t buf,error_t& e);


			//���� �Ƿ��B�ӷ������ɹ�
			inline operator bool() const
			{
				return _client != NULL;
			}

			//�\�Ю��� socket ���� ֱ�� ����ֹͣ �᷵�� 
			//(����ѽ�connect�ɹ� ��t �О� δ���x)
			void run();

			//ֹͣ����
			void stop();
		protected:
			void release();
		public:
			//���_������ ���{
			typedef void (*s_func_closed_t)(client_t*);

			//���յ� �͑��� 1�l������Ϣ�� ���{
			typedef void (*s_func_readed_t)(client_t*,message_t*);

			//�l�� 1�l������Ϣ�� ���{
			typedef void (*s_func_writed_t)(client_t*,std::size_t);
		protected:
			s_func_closed_t _func_closed;
			s_func_readed_t _func_readed;
			s_func_writed_t _func_writed;

		public:
			//�O��/���� socket ̎�� ���{����
			//�O�Þ� NULL(Ĭ�J) ��̎�������¼�
			void closed(s_func_closed_t func);
			void readed(s_func_readed_t func);
			void writed(s_func_writed_t func);
	
			s_func_closed_t closed();
			s_func_readed_t readed();
			s_func_writed_t writed();

			//������� �l�� ��Ϣ
			void write_message(message_t& msg,error_t& e);

		protected:
			std::size_t _id;
		public:
			inline std::size_t new_id()
			{
				return ++_id;
			}
		};

	};
};
