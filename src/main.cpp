
// main.cpp
#pragma once

#include "stdio.h"
#include "win_service.h"
#include "parse_ini.h"
int main(int argc, char **argv)
{
	SetConsoleTitle("pandabob windows service");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); 
	printf("%s \n",  argv[0] );

	char lpCmdLine[64] = {0};
	char szServiceName[256] = {"pandabob_win_Service"};
	char buff[100];
    int ret;

	char lpServicePathName[512] = {0};
	memset(lpServicePathName, 0 , 512);
	GetModuleFileName(NULL, &lpServicePathName[1],   512);   //get exe path 

	char *pre =  &lpServicePathName[1];
	char *p = strrchr( pre, '\\');
	char iniFilePath[512] = {0};
	snprintf( iniFilePath, p-pre + 1, "%s", pre);
	//printf("the ini path is %s \n",iniFilePath);
	strncat( iniFilePath, ("\\win_service.ini"), strlen("\\win_service.ini"));
	
	//system("pause");
    ret = GetIniKeyString("common","serveice_name",iniFilePath,buff);
	if(ret == 0)
	{
		if(buff[0] == '"')
		{
			buff[strlen(buff) - 1 ] = '\0';
			strcpy(szServiceName,&buff[1]);
		}else
		{
			strcpy(szServiceName,buff);
		}
	}
	ret = GetIniKeyString("common","monitor_exe",iniFilePath,buff);
	if(ret == 0 )
		strcpy(wx_service::MonitorExe,buff);
    //printf("ret:%d,%s\n",ret,buff);
	
	if(argc>1){
		sprintf(lpCmdLine, argv[1]);
	}	
	
	wx_service sv ;
	sv.Init();
	strcpy(wx_service::szServiceName,szServiceName);
	//log("the argc is %d , the szServiceName %s , the MonitorExe %s ",argc,wx_service::szServiceName,wx_service::MonitorExe);
	long dwThreadID = ::GetCurrentThreadId();
	
	if (stricmp(lpCmdLine, "-install") == 0)
	{
		if(argc>=3)
		strcpy( szServiceName, argv[2]);
		strcpy( sv.szServiceName, szServiceName);
		if(sv.Install())
			printf("Install Success.");
		else
			printf("Install Failed.");
		Sleep(2000);
	}
	else if (stricmp(lpCmdLine, "-uninstall") == 0)
	{
		if(argc>=3)
		strcpy( szServiceName, argv[2]);
		strcpy( sv.szServiceName, szServiceName);
		if(sv.Uninstall())
			printf("unInstall Success.");
		else
			printf("unInstall Failed.");
		Sleep(2000);
	}
	else if (stricmp(lpCmdLine, "-help") == 0 || stricmp(lpCmdLine, "/?") == 0)
	{
		printf(" Help: \n");
		printf(" win_service.exe [options argv]  \n");
		printf(" e.g:  \n");
		printf(" win_service.exe -install   \n");
		printf(" win_service.exe -uninstall  \n");
		//printf(" win_service.exe serverName");
	}
	else //if( stricmp(lpCmdLine, "-service") )
	{
		log(" StartServiceCtrlDispatcher ... argc=%d", argc); 
		SERVICE_TABLE_ENTRY st[] =
		{
			{ szServiceName, (LPSERVICE_MAIN_FUNCTION)sv.ServiceMain },
			{ NULL, NULL }
		};
		if(argc>=2){
			strcpy( st[0].lpServiceName, argv[1]);
			strcpy( sv.szServiceName, argv[1]);
			
			log(" arg2 = %s", argv[1]);
		}
		//log(" the service name : %s ",szServiceName);
		log(" ServiceName : %s ", st[0].lpServiceName); 

		char error[512]={0};
		if (!::StartServiceCtrlDispatcher(st))
		{
			log("Register Service[%s] Main Function Error! %s", st[0].lpServiceName, GetLastErrorText(error, 512) );
		}
	}

//	getchar();
END:
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7); 
	
	return 0;
}

