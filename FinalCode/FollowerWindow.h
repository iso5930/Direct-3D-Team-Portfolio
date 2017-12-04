#pragma once

#include "WindowUI.h"

class CMouse;
class CPlayer;
class CFollower;
class CItemSign;

class CFollowerWindow : public CWindowUI
{
private:
	// ID
	DWORD m_dwBothSide;
	DWORD m_dwLeftSide;
	DWORD m_dwRightSide;
	DWORD m_dwAmulet;
	DWORD m_dwRing;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// Follower
	CFollower* m_pFollower;
	
	// EquipSign
	CItemSign* m_EquipSign[5];

	// EquipMessage
	CBasicMessage* m_EquipMessage[5];

	// MainWeaponBorderSign
	CBasicSign* m_pMainWeaponBorderSign[3];

	// SubWeaponBorderSign
	CBasicSign* m_pSubWeaponBorderSign[3];

	// AmuletBorderSign
	CBasicSign* m_pAmuletBorderSign[3];

	// LeftRingBorderSign
	CBasicSign* m_pLeftRingBorderSign[3];

	// RightRingBorderSign
	CBasicSign* m_pRightRingBorderSign[3];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Renew();

private:
	////////////////////////////////////////////////////////////////////////// Pick
	void UpdateNonePick();
	void UpdatePick();
	void UpdateInventoryPick();
	void UpdateEquipmentPick();
	void UpdateFollowerEquipmentPick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateInventoryPickIn();
	void UpdateEquipmentPickIn();
	void UpdateFollowerEquipmentPickIn();

	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateInventoryPickOut();
	void UpdateEquipmentPickOut();
	void UpdateFollowerEquipmentPickOut();

	////////////////////////////////////////////////////////////////////////// InEquip
	void UpdateInEquip();
	void UpdateNonePickInEquip();
	void UpdatePickInEquip();
	void UpdateInventoryPickInEquip();
	void UpdateEquipmentPickInEquip();
	void UpdateFollowerEquipmentPickInEquip();

	////////////////////////////////////////////////////////////////////////// InSkill
	void UpdateInSkill();
	void UpdateNonePickInSkill();
	void UpdatePickInSkill();
	void UpdateInventoryPickInSkill();
	void UpdateEquipmentPickInSkill();
	void UpdateFollowerEquipmentPickInSkill();

	////////////////////////////////////////////////////////////////////////// InStat
	void UpdateInStat();
	void UpdateNonePickInStat();
	void UpdatePickInStat();
	void UpdateInventoryPickInStat();
	void UpdateEquipmentPickInStat();
	void UpdateFollowerEquipmentPickInStat();

public: ////////////////////////////////////////////////////////////////////////// Share
	// GetOverItemInFollowerEquip
	Item* GetOverItemInFollowerEquip();

	// GetID
	DWORD GetID(int _iIndex);

public:
	explicit CFollowerWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CFollowerWindow();
};
