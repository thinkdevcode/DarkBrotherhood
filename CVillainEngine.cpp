#ifndef _CVILLAIN_
#include "CVillainEngine.h"
#endif

CVillainEngine::CVillainEngine()
{

}

CVillainEngine *CVillainEngine::Instance()
{
	static CVillainEngine CVE;

	return &CVE;
}

void CVillainEngine::Initialize()
{
	NumPkEntrance = GetPrivateProfileInt("Villain", "NumPkEntrance", 1000, ".\\villain.ini");
	HeroDeathPkLose = GetPrivateProfileInt("Villain", "HeroDeathPkLose", 5, ".\\villain.ini");
	SoulsForPk = GetPrivateProfileInt("Villain", "SoulsForPk", 1, ".\\villain.ini");
	IncreaseStats = GetPrivateProfileInt("Villain", "IncreaseStats", 1, ".\\villain.ini");
	BlackName = GetPrivateProfileInt("Villain", "BlackName", 1, ".\\villain.ini");
}



/***************************GET**********************************/
int CVillainEngine::getVillainStatus(CCreature *pUser)
{
	return CCacheD::Instance()->GetVillainStatus(pUser);
}

int CVillainEngine::getItemStatus(CCreature *pUser) //Legacy
{
	return CCacheD::Instance()->GetItemStatus(pUser);
}

int CVillainEngine::getRank(CCreature *pUser)
{
	return CCacheD::Instance()->GetVillainRank(pUser);
}

int CVillainEngine::getSouls(CCreature *pUser)
{
	return CCacheD::Instance()->GetSoulStatus(pUser);
}



/***************************SET**********************************/
void CVillainEngine::setItemStatus(CCreature *pUser, bool Item) //Legacy
{
	CCacheD::Instance()->SetItemStatus(pUser, Item);
}

void CVillainEngine::setVillainStatus(CCreature *pUser, bool Villain)
{
	CCacheD::Instance()->SetVillainStatus(pUser, Villain);
}

void CVillainEngine::setVillainRank(CCreature *pUser, int Rank)
{
	CCacheD::Instance()->SetVillainRank(pUser, Rank);
}

void CVillainEngine::setSoulStatus(CCreature *pUser, int Souls)
{
	CCacheD::Instance()->SetVillainStatus(pUser, Souls);
}

/***************************FUNC*********************************/
void CVillainEngine::CVEnterWorld(CCreature *pUser)
{
	if (pUser != NULL)
	{
		CSharedData *pSharedData = pUser->GetSharedData();
		int nPK = pSharedData->wPkCount;
		char buf[128];
		sprintf_s(buf, "%d", pSharedData->wPkCount);
		MessageBox(NULL, buf, "", MB_OK);
		/*
		if (nPK >= 1000)
		{
			int nStatus = CVillainEngine::Instance()->getVillainStatus(pUser);
			if (nStatus == 1)
			{
				int nRank = CVillainEngine::Instance()->getRank(pUser);
				string szRank;
				if (nRank == 1)
					szRank = "Initiate of the Dark";
				else if (nRank == 2)
					szRank = "Martyr of the Dark";
				else if (nRank == 3)
					szRank = "Tyrant of the Dark";
				else if (nRank == 4)
					szRank = "Shadow of the Dark";
				else if (nRank == 5)
					szRank = "Abyss of the Dark";
				else if (nRank == 6)
					szRank = "Lord of the Dark";
				else
					szRank = "Error";
				int nSouls = CVillainEngine::Instance()->getSouls(pUser);
				char szMessage[1024];
				wsprintf(szMessage,"<html><head><body><font color=LEVEL>Welcome back Brother!</font><br><br>Name: <font color=LEVEL>%s</font><br>Rank: <font color=LEVEL>%s</font><br>PK Count: <font color=LEVEL>%s</font><br>Total Souls: <font color=LEVEL>%s</font><br><br><font color=LEVEL>News:</font><br><br>11/21/07 : Revamped the Rank system<br>11/20/07 : Completed Ranking system<br>11/17/07 : Most code completed today<br><br><br><br><br><br><br><br><br><br><br><br><br><br>Dark Brotherhood Mod<br>by <font color=LEVEL>GTProductions.org</font></body></html>", pSharedData->wszName, szRank, pSharedData->wPkCount, nSouls);
				pUser->ShowHTML(L"", reinterpret_cast<wchar_t *>(szMessage), NULL);
			}
			if (nStatus == 0)
			{
				CVillainEngine::Instance()->setVillainStatus(pUser, 1);
				CVillainEngine::Instance()->setVillainRank(pUser, 1);
				wchar_t *szMessage = L"<html><head><body><b>Congratulations!</b> You have been accepted into the Dark Brotherhood at the rank of Villain!<br>May you take harvest many more souls for our cause!<br>Take these items...</body></html>";
				pUser->ShowHTML(L"", szMessage, NULL);
				pUser->AddItemToInventory(57, 1000, false, 0, 0, 0);
			}
		}
		*/
	}
}


/****************************************************************/
CVillainEngine::~CVillainEngine()
{

}