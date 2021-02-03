
// win_service.h

#pragma once

#ifndef WIN_SERVICE_H
#define WIN_SERVICE_H


#include "windows.h"


LPTSTR   GetLastErrorText(   LPTSTR   lpszBuf,   DWORD   dwSize   ) ;
void LogEvent(LPCTSTR pszFormat, ...);
void log(LPCTSTR format, ...);

class wx_service
{
public: 
	wx_service();
	~wx_service();

	

	static void Init();
	static BOOL IsInstalled();
	BOOL Install();
	BOOL Uninstall();

	static void WINAPI ServiceMain(DWORD   dwArgc, LPTSTR   *lpszArgv); 
	
	static void WINAPI ServiceStrl(DWORD dwOpcode);
	BOOL OpenService();
	BOOL StopService();
	BOOL PauseService();
	BOOL ResumeService();

	static BOOL bInstall;
	static SERVICE_STATUS_HANDLE hServiceStatus;
	static SERVICE_STATUS status;// service status  
	static DWORD dwThreadID;

	static SC_HANDLE hSCM;
	static SC_HANDLE hService;

	static char   m_lpServicePathName[512];         //the path of the service 
	static char szServiceName[256];
	static BOOL bPause;
	static BOOL bStop;
	static void Run();
	static void Stop();
	static char MonitorExe[128];

};


#endif