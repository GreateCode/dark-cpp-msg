#pragma once

typedef struct _NET_DATA_HEADER_
{
	//ָ��
	DWORD code;
	//�ļ�id
	DWORD id;
	//�ļ��K ƫ��
	DWORD pos;
	//�ļ��K ��С
	DWORD size;
}NET_DATA_HEADER,*PNET_DATA_HEADER;

//�ς� �ļ�
#define DARK_PROTOCOL_UPLOAD_FILE	1
//�O�� �ļ� ��С
#define DARK_PROTOCOL_SET_FILE_INFO	2
//�O�� �ļ� ����
#define DARK_PROTOCOL_SET_FILE_BIN	3

