#include "StdAfx.h"
#include "message_fragmentation.h"


message_fragmentation::message_fragmentation(void)
{
	memset(&_header,0,sizeof(_header));
}


message_fragmentation::~message_fragmentation(void)
{
}
