// dark-cpp-msg.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "dark-cpp-msg.h"


// ���ǵ���������һ��ʾ��
DARKCPPMSG_API int ndarkcppmsg=0;

// ���ǵ���������һ��ʾ����
DARKCPPMSG_API int fndarkcppmsg(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� dark-cpp-msg.h
Cdarkcppmsg::Cdarkcppmsg()
{
	return;
}
