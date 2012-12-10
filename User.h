#pragma once

#ifndef _USER_
	#define _USER_

	#ifndef _CCREATURE_
		#include "CCreature.h"
	#endif

class User : public CCreature
{
public:
	//----------------------------------------------------------------------
	//Class Functions
	//----------------------------------------------------------------------

	//Constructor
	User();

	void SendQuestList(bool GMPacket)
	{
		typedef void (__thiscall *_SEND_QUEST_LIST) (User *, bool);
		_SEND_QUEST_LIST _SendQuestList = (_SEND_QUEST_LIST)0x0081EB20;

		_SendQuestList(this, GMPacket);
	}

	void SendLogout()
	{
		typedef void (__thiscall *_SEND_LOGOUT) (User *);
		_SEND_LOGOUT _SendLogout = (_SEND_LOGOUT)0x0080DA90;
		
		_SendLogout(this);
	}

	void SetKarma(int nKarma)
	{
		typedef void (__thiscall *_SET_KARMA) (User *, int);
		_SET_KARMA _SetKarma = (_SET_KARMA)0x812B10;

		_SetKarma(this, nKarma);
	}

	void DestroyItemReturn(WORD pItem, int nCount)
	{
		typedef void (__thiscall *_DESTROY_ITEM) (User *, WORD, int);
		_DESTROY_ITEM _DestroyItem = (_DESTROY_ITEM)0x8020A0;

		_DestroyItem(this, pItem, nCount);
	}

	bool AddItemToInventory2(WORD pItem)
	{
		typedef bool (__thiscall *_ADD_ITEM) (User *, WORD);
		_ADD_ITEM _AddItem = (_ADD_ITEM)0x7FFD50;

		return (_AddItem(this, pItem));
	}

	//Destructor
	~User();

	//----------------------------------------------------------------------
	//Class Variables
	//----------------------------------------------------------------------

	//DWORD _unknown[354];
	//CSharedData * SharedData;	//1416	0x588
	//DWORD _unknown2[638];
	//DWORD Abnormals;			//3976	0x0F88
	//DWORD _unknown3[714];
	//NOTE: making this a child class 'eats' 8 bytes
	DWORD _unknown3[712];
	DWORD EvalLeft;				//6836	0x1AB4
	DWORD _unknown4[750];
	//DWORD * pSocket;			//9840	0x2670
	DWORD _unknown5[98];		// -1 if uncomment psocket
	DWORD AccountID;			//10236	0x27FC
	DWORD _unknown6[30];
	//L2_NAME_SIZE = 25
	WCHAR Nickname[25];			//10360	0x2878
};

#endif // _USER_