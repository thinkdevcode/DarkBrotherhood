#ifndef _L2EX_
	#include "L2Ex.h"
#endif

#define JMP 0xE9
#define CALL 0xE8
#define NOP 0x90

L2Ex::L2Ex()
{
	dwProcessID = GetCurrentProcessId();

	L2Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, dwProcessID);

	if (!L2Server)
	{
		MessageBox(NULL, "Unable to open L2Server's Process! Please restart the server.", "Error", MB_OK);
		
		ExitProcess(1);
	}
	
}

L2Ex *L2Ex::Instance()
{
	static L2Ex Ex;

	return &Ex;
}

void L2Ex::WriteServerMemory(BYTE *pAddress, LPCVOID pData, BYTE length)
{
	DWORD dwOldProtect = NULL;
	SIZE_T bWritten = NULL;

	if (!VirtualProtect((LPVOID)(pAddress), length, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		MessageBox(NULL, "Unable to change memory protection 1.", "Error", MB_OK);
	}

	if (!WriteProcessMemory(L2Server, (LPVOID)(pAddress), (LPCVOID)pData, length, &bWritten))
	{
		MessageBox(NULL, "Unable to write to memory.", "Error", MB_OK);

		return;
	}

	if (!VirtualProtect((LPVOID)(pAddress), length, dwOldProtect, &dwOldProtect))
	{
		MessageBox(NULL, "Unable to change memory protection 2.", "Error", MB_OK);
	}
	
}

void L2Ex::WriteServerHook(BYTE bType, BYTE *pAddress, DWORD *pFunction, BYTE bNops)
{

	int iSizeBuffer = 5 + bNops;
	BYTE *bBuffer = new BYTE[iSizeBuffer];
	bBuffer[0] = bType;
	*(DWORD *) (bBuffer + 1) = (DWORD)pFunction - (DWORD)(pAddress+5);
	int i = 5;
	while ( bNops > 0)
	{
		bBuffer[i] = NOP;
		++i;
		--bNops;
	}

	WriteServerMemory((BYTE *)pAddress, (LPCVOID)&bBuffer, iSizeBuffer);

	delete[] bBuffer;

}

void L2Ex::HookEnterWorld()
{
	char szEnterWorld[4];
	*(DWORD *)(szEnterWorld) = (DWORD)EnterWorldHandler;
	WriteServerMemory((BYTE *)0xA87738, (LPVOID)&szEnterWorld, 3);

	//WriteServerHook(JMP, (BYTE *)0xA87730, (DWORD *)EnterWorldHandler, 0);
}

L2Ex::~L2Ex()
{

}