#ifndef _L2EX_
	#include "L2Ex.h"
#endif

void LeaveWorldHandler(CCreature *pUser)
{
	UserContainer::Instance()->DeleteUser(pUser);

	//CVillainEngine::Instance()->CVLeaveWorld(pUser);

	pUser->ULeaveWorld();
}