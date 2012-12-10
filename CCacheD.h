#ifndef _CCACHED_
#define _CCACHED_

	#ifndef _GLOBAL_
		#include "Global.h"
	#endif

	#ifndef _CODBC_
		#include "CODBC.h"
	#endif

	#ifndef _CCREATURE_
		#include "CCreature.h"
	#endif

class CCacheD
{
public:
	CCacheD();
	static CCacheD *Instance();
	void InitConnection();

	/***************************GET**********************************/

	int GetVillainStatus(CCreature *pUser);
	int GetItemStatus(CCreature *pUser);
	int GetVillainRank(CCreature *pUser);
	int GetSoulStatus(CCreature *pUser);

	/***************************SET**********************************/

	void SetVillainStatus(CCreature *pUser, bool status);
	void SetItemStatus(CCreature *pUser, bool status);
	void SetVillainRank(CCreature *pUser, int Rank);
	void SetSoulStatus(CCreature *pUser, int Soul);

	/****************************************************************/
	~CCacheD();
	CODBCDatabase CODBC;
};

#endif