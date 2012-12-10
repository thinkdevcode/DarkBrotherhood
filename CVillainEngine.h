#ifndef _CVILLAIN_
	#define _CVILLAIN_

	#ifndef _GLOBAL_
		#include "Global.h"
	#endif

	#ifndef _CSOCKET_
		#include "CSocket.h"
	#endif

	#ifndef _CCREATURE_
		#include "CCreature.h"
	#endif

	#ifndef _L2SERVER_
		#include "L2Server.h"
	#endif

	#ifndef _CCACHED_
		#include "CCacheD.h"
	#endif

	#ifndef _VILLAINCONTAINER_
		#include "CVillainContainer.h"
	#endif

class CVillainEngine
{
public:
	CVillainEngine();
	static CVillainEngine *Instance();
	void Initialize();

	/***************************GET**********************************/

	int getVillainStatus(CCreature *pUser);
	int getItemStatus(CCreature *pUser);
	int getRank(CCreature *pUser);
	int getSouls(CCreature *pUser);

	/***************************SET**********************************/

	void setVillainStatus(CCreature *pUser, bool Villain);
	void setItemStatus(CCreature *pUser, bool Item);
	void setVillainRank(CCreature *pUser, int Rank);
	void setSoulStatus(CCreature *pUser, int Souls);

	/***************************FUNC*********************************/

	void CVEnterWorld(CCreature *pUser);
	void CVLeaveWorld(CCreature *pUser);

	/****************************************************************/

	~CVillainEngine();

private:
	int NumPkEntrance;
	int HeroDeathPkLose;
	int SoulsForPk;
	int IncreaseStats;
	int BlackName;
};

#endif