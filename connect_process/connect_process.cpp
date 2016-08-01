// connect_process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	std::wstring path = L"test_client.exe";
	for(int i=0;i<100;++i)
	{
		ShellExecute(NULL,NULL,path.c_str(),NULL,NULL,SW_SHOW);
		/*
		STARTUPINFOW startupinfo;
		memset(&startupinfo,0,sizeof(STARTUPINFOW));
		startupinfo.cb=sizeof(STARTUPINFOW);
		PROCESS_INFORMATION process_information;
		std::cout<<"process "<<i<<" RUN = "<<CreateProcessW(NULL,(LPWSTR)path.c_str(),0,0,TRUE,0,0,NULL,&startupinfo,&process_information)<<"\n";
	*/
	}

	return 0;
}

