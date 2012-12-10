#ifndef _DLLMAIN_
	#define _DLLMAIN_

	#ifndef _L2EX_
		#include "L2Ex.h"
	#endif

__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved);

#endif