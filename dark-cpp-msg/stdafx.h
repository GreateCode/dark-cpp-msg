// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#ifdef DARKCPPMSG_EXPORTS
#define DARKCPPMSG_API __declspec(dllexport)
#else
#define DARKCPPMSG_API __declspec(dllimport)
#endif

#include <deque>

#include <boost/unordered_map.hpp>
#include <boost/typeof/typeof.hpp>

#include <dark-cpp/net/tcp.hpp>

#include "error_t.h"