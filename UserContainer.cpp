#ifndef _USERCONTAINER_
	#include "UserContainer.h"
#endif

UserContainer::UserContainer()
{

}

UserContainer *UserContainer::Instance()
{
	static UserContainer UC;

	return &UC;
}

void UserContainer::AddUser(CCreature *pUser)
{
	pContainer.push_back(pUser);
}

void UserContainer::DeleteUser(CCreature *pUser)
{
	for (UCIT = pContainer.begin(); UCIT != pContainer.end(); UCIT++)
	{
		if (pUser == *UCIT)
		{

			pContainer.erase(UCIT);
		}
	}
}

bool UserContainer::UserExists(CCreature *pUser)
{
	for (UCIT = pContainer.begin(); UCIT != pContainer.end(); UCIT++)
	{
		if (pUser == *UCIT)
		{

			return true;
		}
	}

	return false;
}

CCreature *UserContainer::GetUserByName(wchar_t *szName)
{
	for (UCIT = pContainer.begin(); UCIT != pContainer.end(); UCIT++)
	{
		CCreature *pCreature = reinterpret_cast<CCreature *>(*UCIT);
		CSharedData *pSharedData = pCreature->GetSharedData();

		if (wcscmp(pSharedData->wszName, szName) == 0)
		{

			return *UCIT;
		}
	}

	return NULL;
}

CCreature *UserContainer::GetUserByObjId(int iObjId)
{
	for (UCIT = pContainer.begin(); UCIT != pContainer.end(); UCIT++)
	{
		CCreature *pCreature = reinterpret_cast<CCreature *>(*UCIT);
		CSharedData *pSharedData = pCreature->GetSharedData();

		if (pSharedData->nObjectID == iObjId)
		{

			return *UCIT;
		}
	}

	return NULL;
}

CCreature *UserContainer::GetUserByNpcIndex(int iNpcIndex)
{
	for (UCIT = pContainer.begin(); UCIT != pContainer.end(); UCIT++)
	{
		CCreature *pCreature = reinterpret_cast<CCreature *>(*UCIT);
		CSharedData *pSharedData = pCreature->GetSharedData();

		if (pSharedData->nNpcIndex == iNpcIndex)
		{

			return *UCIT;
		}
	}

	return NULL;
}

UserContainer::~UserContainer()
{

}