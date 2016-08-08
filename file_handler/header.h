#pragma once

#define DK_FILE_HANDLER_CODE_FILE_INFO	1
#define DK_FILE_HANDLER_CODE_FILE_DATA	2
typedef struct _FILE_INFO_
{
	DWORD code;	//�������R
	DWORD id;	//�ļ�id
	DWORD size;	//�ļ��L
	DWORD len;	//�ļ����L
	char name[1];
}FILE_INFO,*PFILE_INFO;
typedef struct _FILE_DATA_
{
	DWORD code;		//�������R
	DWORD id;		//�ļ�id
	DWORD offset;	//����ƫ��
	DWORD size;		//������С
	char data[1];
}FILE_DATA,*PFILE_DATA;