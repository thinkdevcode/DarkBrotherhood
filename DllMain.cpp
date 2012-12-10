#ifndef _DLLMAIN_
	#include "DllMain.h"
#endif

__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CVillainEngine::Instance()->Initialize();
			CCacheD::Instance()->InitConnection();
			L2Ex::Instance()->HookEnterWorld();
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}
	return true;
}