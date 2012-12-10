#ifndef _L2EX_
	#include "L2Ex.h"
#endif

void EnterWorldHandler(CCreature *pUser)
{
	pUser->UEnterWorld();
	UserContainer::Instance()->AddUser(pUser);
	CVillainEngine::Instance()->CVEnterWorld(pUser);
}