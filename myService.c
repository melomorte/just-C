//codigo original - https://github.com/samoylenko/service/blob/master/service.c

#define _CRT_SECURE_NO_WARNINGS //removeos avsos de segurança do pré-processador.

//#pragma comment - faz comentarios para o linker saber como executar corretamente.
#pragma comment(lib, "kernel32.lib")	//diz para usar a lib kernel32.lib
#pragma comment(lib, "advapi32.lib")	//diz para usar a lib advapi32.lib
#pragma comment(lib, "shell32.lib")		//diz para usar a lib shell32.lib

//definindo os nomes.
#define SZAPPNAME				"melomorte"				//appname.
#define SZSERVICENAME			"MelomorteService"		//service name.
#define SZSERVICEDISPLAYNAME	"melomorte service"		//display name.
#define SZDEPENDENCIES			""						//informa as dependencias.

//headers.
#include <windows.h>	//biblioteca padrão do windows.
#include <stdio.h>		//entrada e saida padrão.
#include <stdlib.h>		//controle de processos e alocação de memoria.
#include <tchar.h>		//multibyte e unicode.

//status so serviço.
SERVICE_STATUS			ssStatus;					//estrutura usada para informar o status do serviço ao gerente de3 controle.
SERVICE_STATUS_HANDLE	sshStatusHandle;			//Um identificador para a estrutura de informações de status do serviço atual.
DWORD					dwErr = 0;					//dword para erro.
BOOL					bDebug = FALSE;				//debug.
TCHAR 					szErr[256];					//aloca 256 bytes para erro.
HANDLE 					hServerStopEvent = NULL;	//pausa os eventos do serviço.

//declaração de funções.
VOID serviceStart(DWORD dwArgc, LPTSTR *lpszArgv);
VOID serviceStop();
BOOL reportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);
void addToMessageLog(LPCTSTR lpszMsg);
VOID WINAPI service_ctrl(DWORD dwCtrlCode);
VOID WINAPI service_main(DWORD dwArgc, LPTSTR *lpszArgv);
VOID cmdInstallService();
VOID cmdRemoveService();
VOID cmdDebugService(int argc, char **argv);
BOOL WINAPI ControlHandler(DWORD dwCtrlType);
LPTSTR GetLastErrorText(LPTSTR lpszBuf, DWORD dwSize);

/*--------------------------------------SERVICE START--------------------------------------*/
VOID serviceStart(DWORD dwArgc, LPTSTR *lpszArgv)
{
	HANDLE hEvents[2] = {NULL, NULL};									//define um handle para events.

	//vai testar o status e chama a função cleanup.
	if(!reportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR,3000))
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	hServerStopEvent = CreateEvent( NULL, TRUE, FALSE, NULL);
	if (hServerStopEvent == NULL)
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	hEvents[0] = hServerStopEvent;

	if(!reportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	hEvents[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(hEvents[1] == NULL)
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	if (!reportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	if (!reportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0))
	{
		if(hServerStopEvent)
		{
			CloseHandle(hServerStopEvent);
		}

		if (hEvents[1])
		{
			CloseHandle(hEvents[1]);
		}
	}

	while(1)
	{
		/*-------*/
	}
}
/*--------------------------------------SERVICE STOP--------------------------------------*/
VOID serviceStop()
{
	if (hServerStopEvent)
	{
		setEvent(hServerStopEvent);
	}
}
/*--------------------------------------MAIN FUNCTION--------------------------------------*/
int main(int argc, char **argv)
{
	TCHAR szName[] = TEXT(SZSERVICENAME); 	//chama o nome do serviço.
	SERVICE_TABLE_ENTRY dispatchTable[] = {{ szName, service_main } , { NULL, NULL }};

	//reinicia automaticamene
	/*#include <windows.h>
	#include <stdio.h>
	int main(int argc,char*Arquivo[]); // Novamente Arquivo[0] será o executável (use GetModuleFileName() caso seu programa seja Win API.
	{
	char*homedrive=getenv("homedrive");//pega o disco local, geralmente C:
	char destino[9999]; // o destino do arquivo
	strcpy(destino,homedrive);
	strcat(destino,"//Nomedoarquivo.exe");
	CopyFile(Arquivo[0],destino,0); // use if(CopyFile()) para melhores resultados
	// o arquivo já está no C:, agora vamos criar a entrada no registro para que ele se autoinicie.
	HKEY Entrada;
	RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",&Entrada); 
	RegSetValueEx(Entrada,"Nomedaentrada",0,1,(LPBYTE)destino,25); 
	RegCloseKey(Entrada);
	//Pronto, agora continue seu código e, quando o windows se inicializar novamente o programa será auto-executado.
	}//fim do programa.*/

	/*MENU*/
	if ((argc > 1) && ((*argv[1] == '-') || (*argv[1] == '/')))
	{
		if (_stricmp("install", argv[1] + 1) == 0) 				/* instala o serviço */
		{
			cmdInstallService();
		}
		else if (_stricmp("remove", argv[1] + 1) == 0)			/* remove o serviço */
		{
			cmdRemoveService();
		}
		else if (_stricmp("debug", argv[1] + 1) == 0)			/* debuga o serviço */
		{
			bDebug = TRUE;
			cmdDebugService(argc, argv);
		}
		else
		{
			//OPÇÕES.
			printf("%s -install\n", SZAPPNAME);
			printf("%s -remove\n", SZAPPNAME);
			printf("%s -debug <params> \n", SZAPPNAME);
			printf("\nStartServiceCtrlDispatcher being called\n");

			if (!nStartServiceCtrlDispatcher(dispatchTable))
			{
				addToMessageLog(TEXT("StartServiceCtrlDispatcher - failed."));
			}
		}
	}
	return 0;
}
/*--------------------------------------SERVICE MAIN--------------------------------------*/
void WINAPI service_main(DWORD dwArgc, LPTSTR *lpszArgv)
{
	sshStatusHandle = RegisterServiceCtrlHandle(TEXT(SZSERVICENAME), service_ctrl);

	if (!sshStatusHandle)
	{
		if (sshStatusHandle)
		{
			(VOID)reportStatusToSCMgr(SERVICE_STOPPED, dwErr, 0);
		}
	}

	serviceStart(dwArgc, lpszArgv);

	return;
}
/*--------------------------------------SERVICE CTRL--------------------------------------*/
VOID WINAPI service_ctrl(DWORD dwCtrlCode)
{
	switch(dwCtrlCode)
	{
		case SERVICE_CONTROL_STOP:
			reportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);
			serviceStop();
			return;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			break;
	}

	reportStatusToSCMgr(ssStatus.dwCurrentState, NO_ERROR, 0);
}
/*--------------------------------------REPORT STATUS--------------------------------------*/
BOOL reportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
	static DWORD dwCheckPoint = 1;
	BOOL fResult = TRUE;

	if (!bDebug)
	{
		if (dwCurrentState == SERVICE_START_PENDING)
		{
			ssStatus.dwControlsAccepted = 0;
		}
		else
		{
			ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
		}

		ssStatus.dwCurrentState  = dwCurrentState;
		ssStatus.dwWin32ExitCode = dwWin32ExitCode;
		ssStatus.dwWaitHint		 = dwWaitHint;

		if ((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED))
		{
			ssStatus.dwCheckPoint = 0;
		}
		else
		{
			ssStatus.dwCheckPoint = dwCheckPoint++;
		}

		if (!(fResult = SetServiceStatus(sshStatusHandle, &ssStatus)))
		{
			addToMessageLog(TEXT("SetServiceStatus"));
		}
	}

	return fResult;
}
/*--------------------------------------ADD TO MESSAGE LOG--------------------------------------*/
VOID addToMessageLog(LPCTSTR lpszMsg)
{
	TCHAR 	szMsg[256];
	HANDLE 	hEventSource;
	LPCTSTR	lpszStrings[2];

	if (!bDebug)
	{
		dwErr = GetLastError();

		hEventSource = RegisterEventSource(NULL, TEXT(SZSERVICENAME));

		_stprintf(szMsg, TEXT("%s error: %d"), TEXT(SZSERVICENAME));
		lpszStrings[0] = szMsg;
		lpszStrings[1] = lpszMsg;

		if (hEventSource != NULL)
		{
				ReportEvent(
					hEventSource,
					EVENTLOG_ERROR_TYPE,
					0,
					0,
					NULL,
					2,
					0,
					lpszStrings,
					NULL);
		}
		(VOID)DeregisterEventSource(hEventSource);
	}
}
/*--------------------------------------INSTALL SERVICE--------------------------------------*/
void cmdInstallService()
{
	SC_HANDLE schService;
	SC_HANDLE schSCManager;

	TCHAR szPath[512];

	if (GetModuleFileName(NULL, szPath, 512) == 0)
	{
		_tprintf(TEXT("unable to install %s - %s\n"), TEXT(SZSERVICEDISPLAYNAME), GetLastErrorText(szErr, 256));
		return;
	}

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(schSCManager != NULL)
	{
		schService = CreateService(
			schSCManager,
			TEXT(SZSERVICENAME),
			TEXT(SZSERVICEDISPLAYNAME),
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			szPath,
			NULL,
			NULL,
			TEXT(SZDEPENDENCIES),
			NULL,
			NULL);

		if(schService)
		{
			_tprintf(TEXT("%s installed.\n"), TEXT(SZSERVICEDISPLAYNAME));
			CloseServiceHandle(schService);
		}
		else
		{
			_tprintf(TEXT("CreateService failed - %s\n"), GetLastErrorText(szErr, 256));
		}

		CloseServiceHandle(schSCManager);
	}
	else
	{
		_tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr, 256));
	}
}
/*--------------------------------------REMOVE SERVICE--------------------------------------*/
void cmdRemoveService()
{
	SC_HANDLE schService;
	SC_HANDLE schSCManager;

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager)
	{
		schService = OpenService(schSCManager, TEXT(SZSERVICENAME), SERVICE_ALL_ACCESS);

		if (schService)
		{
			if (ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
			{
				_tprintf(TEXT("stopping %s."), TEXT(SZSERVICEDISPLAYNAME));
				sleep(500);

				while(QueryServiceStatus(schService, &ssStatus))
				{
					if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
					{
						_tprintf(TEXT("."));
						sleep(500);
					}
					else
					{
						break;
					}
				}

				if (ssStatus.dwCurrentState == SERVICE_STOPPED)
				{
					_tprintf(TEXT("\n%s stopped.\n"), TEXT(SZSERVICEDISPLAYNAME));
				}
				else
				{
					_tprintf(TEXT("\n%s stopped - failed - %s\n"), TEXT(SZSERVICEDISPLAYNAME));
				}
			}

			if (DeleteService(schService))
			{
				_tprintf(TEXT("%s removed. \n"), TEXT(SZSERVICEDISPLAYNAME));
			}
			else
			{
				_tprintf(TEXT("DeleteService - failed. - %s\n"), GetLastErrorText(szErr, 256));
			}

			CloseServiceHandle(schSCManager);
		}
		else
		{
			_tprintf(TEXT("OpenSCManager - failed - %s\n"), GetLastErrorText(szErr, 256));
		}
	}
}
/*--------------------------------------REMOVE SERVICE--------------------------------------*/
void cmdDebugService(int argc, char **argv)
{
	DWORD dwArgc;
	LPTSTR *lpszArgv;

#ifdef UNICODE
	lpszArgv = CommandLineToArgvW(GetCommandLineW(), &dwArgc);
#else
	dwArgc   = (DWORD)argc;
	lpszArgv = argv;
#endif

	_tprintf(TEXT("Debugging %s.\n"), TEXT(SZSERVICEDISPLAYNAME));

	SetConsoleCtrlHandler(ControlHandler, TRUE);

	ServiceStart(dwArgc, lpszArgv);
}
/*--------------------------------------CONTROL HANDLER--------------------------------------*/
BOOL WINAPI ControlHandler(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_BREAK_EVENT:
	case CTRL_C_EVENT:
		_tprintf(TEXT("Stopping %s.\n"), TEXT(SZSERVICEDISPLAYNAME));
		ServiceStop();
		return TRUE;
		break;

	}
	return FALSE;
}
/*--------------------------------------GET LAST ERROR TEXT--------------------------------------*/
LPTSTR GetLastErrorText(LPTSTR lpszBuf, DWORD dwSize)
{
	DWORD dwRet;
	LPTSTR lpszTemp = NULL;

	dwRet = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		GetLastError(),
		LANG_NEUTRAL,
		(LPTSTR)&lpszTemp,
		0,
		NULL);

	if(!dwRet || ((long)dwSize < (long)dwRet + 14))
	{
		lpszBuf[0] = TEXT('\0');
	}
	else
	{
		lpszTemp[lstrlen(lpszTemp) - 2] = TEXT('\0');
		_stprintf(lpszBuf, TEXT("%s (0x%x)"), lpszTemp, GetLastError());
	}

	if(lpszTemp)
	{
		LocalFree((HLOCAL)lpszTemp);
	}

	return lpszBuf;
}
