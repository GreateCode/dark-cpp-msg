// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <WinSock2.h>


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <string>
#include <iostream>


#define TEXT_HANDLER_API __declspec(dllexport)

#include "../dark-cpp-msg/dk/net/tcp.h"

#ifdef _DEBUG
#pragma comment(lib,"../debug/dark-cpp-msg-mdd.lib")
#else
#pragma comment(lib,"../release/dark-cpp-msg-md.lib")
#endif
