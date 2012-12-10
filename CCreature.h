#ifndef _CCREATURE_
	#define _CCREATURE_

	#ifndef _CSHAREDDATA_
		#include "CSharedData.h"
	#endif

class CCreature
{
public:
	CCreature();

	void AcquireSkill(unsigned int skillID, int level)
	{
		typedef void (__thiscall *_ACQUIRE_SKILL) (CCreature*, unsigned int, int);
		_ACQUIRE_SKILL _AcquireSkill = (_ACQUIRE_SKILL)0x004F8760;

		_AcquireSkill(this, skillID, level);
	}

	void DeleteAquireSkill(int skillID)
	{
		typedef void (__thiscall *_DELETE_ACQUIRE_SKILL) (CCreature *, int);
		_DELETE_ACQUIRE_SKILL _DeleteAcquireSkill = (_DELETE_ACQUIRE_SKILL)0x004F8A70;

		_DeleteAcquireSkill(this, skillID);
	}

	bool HaveSkill(int skillID, int level)
	{
		typedef bool (__thiscall *_HAVE_SKILL) (CCreature *, int, int);
		_HAVE_SKILL _HaveSkill = (_HAVE_SKILL)0x004F0830;

		return ( _HaveSkill(this, skillID, level) );
	}

	void ModifyAcquireSkill(int skillID, int level)
	{
		typedef void (__thiscall *_MODIFY_ACQUIRE_SKILL) (CCreature *, int, int);
		_MODIFY_ACQUIRE_SKILL _ModifyAcquireSkill = (_MODIFY_ACQUIRE_SKILL)0x004F8BD0;

		_ModifyAcquireSkill(this, skillID, level);
	}

	void AddItemToInventory(int nItemClassID, int nCount, bool bIsPick, int nEnchanted, int nBless, int nEroded)
	{
		typedef void (__thiscall *_ADD_ITEM_TO_INVENTORY) (CCreature *, int, int, bool, int, int, int);
		_ADD_ITEM_TO_INVENTORY _AddItemToInventory = (_ADD_ITEM_TO_INVENTORY)0x4EF130;

		_AddItemToInventory(this, nItemClassID, nCount, bIsPick, nEnchanted, nBless, nEroded);
	}

	void UEnterWorld()
	{
		typedef void (__thiscall *_UENTER_WORLD)(CCreature *);
		_UENTER_WORLD _UEnterWorld = (_UENTER_WORLD)0x84CED0;

		_UEnterWorld(this);
	}

	void ShowHTML(wchar_t *filename, wchar_t *buffer, int classID)
	{
		typedef void (__thiscall *_SHOW_HTML)(CCreature *, wchar_t *, wchar_t *, int);
		_SHOW_HTML _ShowHTML = (_SHOW_HTML)0x80A060;

		_ShowHTML(this, filename, buffer, classID);
	}

	void ULeaveWorld()
	{
		typedef void (__thiscall *_ULEAVE_WORLD)(CCreature *);
		_ULEAVE_WORLD _ULeaveWorld = (_ULEAVE_WORLD)0x84FE10;

		_ULeaveWorld(this);
	}

	CSharedData *GetSharedData()
	{
		return pSharedData;
	}


	~CCreature();

private:

	int iUnk1[354]; // 0x00

	CSharedData *pSharedData; // 0x588

	int iUnk2[638]; // 0x590
	int iAbnormals; // 0xF88
	int iUnk3[1465]; // 0xF8C
	int pSocket; // 0x2670
	int iUnk4[98]; // 0x2674
	int iAccountId; //0x27FC
	int iUnk5[30]; // 0x2800

	wchar_t szNickName[25]; // 0x2878

	int iUnk6[215]; // 0x28AC

	int iPrivateStore; // 0x2C08
};

#endif