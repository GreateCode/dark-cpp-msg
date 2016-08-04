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
		//消息分 頭
		typedef struct _MESSAGE_HEADER_
		{
			//消息頭 標記 固定為 
			//std::size_t flag;
			char flag[4];

			//消息 唯一標識符
			std::size_t id;

			//消息長度數量
			std::size_t size;
		}MESSAGE_HEADER,*PMESSAGE_HEADER;


	};
};