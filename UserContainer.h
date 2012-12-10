#ifndef _USERCONTAINER_
#define _USERCONTAINER_

#ifndef _CCREATURE_
	#include "CCreature.h"
#endif

#ifndef _GLOBAL_
	#include "Global.h"
#endif

class UserContainer
{
public:

	UserContainer();

	static UserContainer *Instance();

	void AddUser(CCreature *pUser);
	void DeleteUser(CCreature *pUser);

	bool UserExists(CCreature *pUser);

	CCreature *GetUserByName(wchar_t *szName);
	CCreature *GetUserByObjId(int iObjId);
	CCreature *GetUserByNpcIndex(int iNpcIndex);

	~UserContainer();

private:

	vector<CCreature *> pContainer;
	vector<CCreature *>::iterator UCIT;

};

#endif