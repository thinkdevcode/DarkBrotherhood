#ifndef _L2EX_
	#define _L2EX_

	#ifndef _CVILLAIN_
		#include "CVillainEngine.h"
	#endif

	#ifndef _USERCONTAINER_
		#include "UserContainer.h"
	#endif

extern "C"
{
	void EnterWorldHandler(CCreature *pUser);
	void LeaveWorldHandler(CCreature *pUser);
}

class L2Ex
{
public:

	L2Ex();
	static L2Ex *Instance();
	void WriteServerMemory(BYTE *pAddress, LPCVOID pData, BYTE length);
	void WriteServerHook(BYTE bType, BYTE *pAddress, DWORD *pFunction, BYTE bNops);

	void HookEnterWorld();

	~L2Ex();

private:

	HANDLE L2Server;
	DWORD dwProcessID;

};

#endif