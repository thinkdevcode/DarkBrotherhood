#ifndef _CCACHED_
	#include "CCacheD.h"
#endif

#pragma warning (disable: 4996)

CCacheD::CCacheD()
{

}

CCacheD *CCacheD::Instance()
{
	static CCacheD CacheD;

	return &CacheD;
}

void CCacheD::InitConnection()
{
	char szUsername[16];
	GetPrivateProfileString("Database", "Username", "", szUsername, 16, ".//villain.ini");

	char szPassword[16];
	GetPrivateProfileString("Database", "Password", "", szPassword, 16, ".//villain.ini");

	char szDatabase[16];
	GetPrivateProfileString("Database", "DbName", "", szDatabase, 16, ".//villain.ini");

	char szConnString[256];
	sprintf_s(szConnString, 256, "Driver={SQL Server};Server=(local);"
								 "Trusted_Connection=no;"
								 "Database=%s;Uid=%s;Pwd=%s;", szDatabase, szUsername, szPassword);

	CODBC.SetConnectionTimeout(30);

	if (!CODBC.DriverConnect(szConnString))
	{
		MessageBox(NULL, "Could not connect to database! Please check your connection settings.", "L2Ex[Villain]", MB_OK);

		ExitProcess(0);
	}
}

/***************************GET**********************************/
int CCacheD::GetVillainStatus(CCreature *pUser)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();
		
		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		ODBCRSet.Open("SELECT villain_status FROM user_data WHERE char_name='%s'", szCharName);

		while (!ODBCRSet.IsEof())
		{
			int nIsVillain;
			ODBCRSet.GetFieldValue(0, (LONG *)&nIsVillain);
			return nIsVillain;

			ODBCRSet.MoveNext();
		}

		ODBCRSet.Close();
		
	}
}

int CCacheD::GetItemStatus(CCreature *pUser)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();
		
		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		ODBCRSet.Open("SELECT item_status FROM user_data WHERE char_name='%s'", szCharName);

		while (!ODBCRSet.IsEof())
		{
			int nItem;
			ODBCRSet.GetFieldValue(0, (LONG *)&nItem);
			return nItem;

			ODBCRSet.MoveNext();
		}

		ODBCRSet.Close();
		
	}
}

int CCacheD::GetVillainRank(CCreature *pUser)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();
		
		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		ODBCRSet.Open("SELECT villain_rank FROM user_data WHERE char_name='%s'", szCharName);

		while (!ODBCRSet.IsEof())
		{
			int nVRank;
			ODBCRSet.GetFieldValue(0, (LONG *)&nVRank);
			return nVRank;

			ODBCRSet.MoveNext();
		}

		ODBCRSet.Close();
		
	}
}

int CCacheD::GetSoulStatus(CCreature *pUser)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();
		
		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		ODBCRSet.Open("SELECT soul_status FROM user_data WHERE char_name='%s'", szCharName);

		while (!ODBCRSet.IsEof())
		{
			int nVSouls;
			ODBCRSet.GetFieldValue(0, (LONG *)&nVSouls);
			return nVSouls;

			ODBCRSet.MoveNext();
		}

		ODBCRSet.Close();
		
	}
}

/***************************SET**********************************/
void CCacheD::SetVillainStatus(CCreature *pUser, bool Status)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();

		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		if (!ODBCRSet.Open("UPDATE user_data SET villain_status=%d WHERE char_name='%s'", Status, szCharName))
		{
			//error
		}
		
	}
}

void CCacheD::SetItemStatus(CCreature *pUser, bool Status)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();

		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		if (!ODBCRSet.Open("UPDATE user_data SET item_status=%d WHERE char_name='%s'", Status, szCharName))
		{
			//error
		}
		
	}
}
void CCacheD::SetVillainRank(CCreature *pUser, int Rank)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();

		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		if (!ODBCRSet.Open("UPDATE user_data SET villain_rank=%d WHERE char_name='%s'", Rank, szCharName))
		{
			//error
		}
		
	}
}

void CCacheD::SetSoulStatus(CCreature *pUser, int Soul)
{
	if (pUser != NULL)
	{
		
		CSharedData *pSharedData = pUser->GetSharedData();

		CODBCRecordset ODBCRSet = CODBCRecordset(&CODBC);

		char szCharName[16];
		wcstombs(szCharName, pSharedData->wszName, 16);
		if (!ODBCRSet.Open("UPDATE user_data SET soul_status=%d WHERE char_name='%s'", Soul, szCharName))
		{
			//error
		}
		
	}
}
CCacheD::~CCacheD()
{

}