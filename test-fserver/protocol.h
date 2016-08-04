#pragma once

typedef struct _NET_DATA_HEADER_
{
	//指令
	DWORD code;
	//文件id
	DWORD id;
	//文件塊 偏移
	DWORD pos;
	//文件塊 大小
	DWORD size;
}NET_DATA_HEADER,*PNET_DATA_HEADER;

//上傳 文件
#define DARK_PROTOCOL_UPLOAD_FILE	1
//設置 文件 大小
#define DARK_PROTOCOL_SET_FILE_INFO	2
//設置 文件 數據
#define DARK_PROTOCOL_SET_FILE_BIN	3

