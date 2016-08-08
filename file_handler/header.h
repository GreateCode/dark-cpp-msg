#pragma once

#define DK_FILE_HANDLER_CODE_FILE_INFO	1
#define DK_FILE_HANDLER_CODE_FILE_DATA	2
typedef struct _FILE_INFO_
{
	DWORD code;	//操作標識
	DWORD id;	//文件id
	DWORD size;	//文件長
	DWORD len;	//文件名長
	char name[1];
}FILE_INFO,*PFILE_INFO;
typedef struct _FILE_DATA_
{
	DWORD code;		//操作標識
	DWORD id;		//文件id
	DWORD offset;	//數據偏移
	DWORD size;		//數據大小
	char data[1];
}FILE_DATA,*PFILE_DATA;