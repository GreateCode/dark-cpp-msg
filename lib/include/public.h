#pragma once

#include "error_t.h"
namespace dk
{
	namespace net
	{

#define DK_ERROR_VALUE_BASE				1102 * 666
#define DK_ERROR_VALUE_MEMORY_EMPTY		DK_ERROR_VALUE_BASE + 1
#define DK_ERROR_VALUE_NOT_FOUNT		DK_ERROR_VALUE_BASE + 100

#define DK_ERROR_VALUE_SERVER_REJECT	DK_ERROR_VALUE_BASE + 1000
#define DK_ERROR_VALUE_LISTEN_ERROR		DK_ERROR_VALUE_BASE + 200


#define DK_MESSAGE_HEADER_FLAG_COUNT	4
#define DK_MESSAGE_HEADER_FLAG_0		0x4E
#define DK_MESSAGE_HEADER_FLAG_1		0x04
#define DK_MESSAGE_HEADER_FLAG_2		0x0
#define DK_MESSAGE_HEADER_FLAG_3		0x0
//#define DK_MESSAGE_HEADER_FLAG			0x0000044E
		//��Ϣ�� �^
		typedef struct _MESSAGE_HEADER_
		{
			//��Ϣ�^ ��ӛ �̶��� 
			//std::size_t flag;
			char flag[4];

			//��Ϣ Ψһ���R��
			std::size_t id;

			//��Ϣ�L�Ȕ���
			std::size_t size;
		}MESSAGE_HEADER,*PMESSAGE_HEADER;


	};
};