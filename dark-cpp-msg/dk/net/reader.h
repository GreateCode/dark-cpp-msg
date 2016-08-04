#pragma once
#include "message.h"
namespace dk
{
	namespace net
	{
		class reader
		{
		public:
			reader(void);
			~reader(void);

			bool get_message(const char* data,std::size_t size,message* p_msg);
		protected:
			//�xȡ ���n�^
			std::vector<char> _datas;
			typedef std::vector<char>::iterator iterator_t;

			bool get_message(message* p_msg);

			message_data_ptr_t _data;

			message_data_ptr_t read_header();
			//���x body
			std::size_t _size;

			//���� ��һ�� ��Ƭ�^ �K�҄h�� �e�`���� (��Ƭ�^ ֮ǰ�� ����)
			//���� true �絽��Ƭ�^ false δ�ҵ�
			bool find_reader();
		};

	};
};