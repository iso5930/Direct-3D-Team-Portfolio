#pragma once

#include "WindowUI.h"

class CMouse;
class CPlayer;
class CFollower;
class CItemSign;
class CBasicSign;
class CBasicMessage;

class CInvenWindow : public CWindowUI
{
protected:
	// ID
	DWORD m_dwBothSide;
	DWORD m_dwLeftSide;
	DWORD m_dwRightSide;
	DWORD m_dwShoulders;
	DWORD m_dwHelms;
	DWORD m_dwAmulet;
	DWORD m_dwGloves;
	DWORD m_dwChestArmor;
	DWORD m_dwBracers;
	DWORD m_dwRing;
	DWORD m_dwBelt;
	DWORD m_dwPants;
	DWORD m_dwBoots;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// Follower
	CFollower* m_pFollower;

	// InvenSign
	vector<CItemSign*> m_InvenSign;

	// EquipSign
	CItemSign* m_EquipSign[13];

	// EquipMessage
	CBasicMessage* m_EquipMessage[13];

	// BorderSign
	CBasicSign* m_pBorderSign[3];

	// MainWeaponBorderSign
	CBasicSign* m_pMainWeaponBorderSign[3];

	// HelmsBorderSign
	CBasicSign* m_pHelmsBorderSign[3];

	// SholdersBorderSign
	CBasicSign* m_pSholdersBorderSign[3];

	// ChestArmorBorderSign
	CBasicSign* m_pChestArmorBorderSign[3];

	// BracersBorderSign
	CBasicSign* m_pBracersBorderSign[3];

	// GlovesBorderSign
	CBasicSign* m_pGlovesBorderSign[3];

	// BeltBorderSign
	CBasicSign* m_pBeltBorderSign[3];

	// PantsBorderSign
	CBasicSign* m_pPantsBorderSign[3];

	// BootsBorderSign
	CBasicSign* m_pBootsBorderSign[3];

	// AmuletBorderSign
	CBasicSign* m_pAmuletBorderSign[3];

	// LeftRingBorderSign
	CBasicSign* m_pLeftRingBorderSign[3];

	// RightRingBorderSign
	CBasicSign* m_pRightRingBorderSign[3];

	// SubWeaponBorderSign
	CBasicSign* m_pSubWeaponBorderSign[3];

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
	void UpdateStoragePick();
	void UpdateStorePick();
	void UpdateDecomposePick();
	void UpdateFollowerEquipPick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateInventoryPickIn();
	void UpdateEquipmentPickIn();
	void UpdateStoragePickIn();
	void UpdateStorePickIn();
	void UpdateDecomposePickIn();
	void UpdateFollowerEquipPickIn();

	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateInventoryPickOut();
	void UpdateEquipmentPickOut();
	void UpdateStoragePickOut();
	void UpdateStorePickOut();
	void UpdateDecomposePickOut();
	void UpdateFollowerEquipPickOut();

	////////////////////////////////////////////////////////////////////////// InInven
	void UpdateInInven();
	void UpdateNonePickInInven();
	void UpdatePickInInven();
	void UpdateInventoryPickInInven();
	void UpdateEquipmentPickInInven();
	void UpdateStoragePickInInven();
	void UpdateStorePickInInven();
	void UpdateDecomposePickInInven();
	void UpdateFollowerEquipPickInInven();

	////////////////////////////////////////////////////////////////////////// InEquip
	void UpdateInEquip();
	void UpdateNonePickInEquip();
	void UpdatePickInEquip();
	void UpdateInventoryPickInEquip();
	void UpdateEquipmentPickInEquip();
	void UpdateStoragePickInEquip();
	void UpdateStorePickInEquip();
	void UpdateDecomposePickInEquip();
	void UpdateFollowerEquipPickInEquip();

	////////////////////////////////////////////////////////////////////////// InStat
	void UpdateInStat();
	void UpdateNonePickInStat();
	void UpdatePickInStat();
	void UpdateInventoryPickInStat();
	void UpdateEquipmentPickInStat();
	void UpdateStoragePickInStat();
	void UpdateStorePickInStat();
	void UpdateDecomposePickInStat();
	void UpdateFollowerEquipPickInStat();

public: ////////////////////////////////////////////////////////////////////////// Share
	// GetOverItemInInven
	Item* GetOverItemInInven();

	// GetOverItemInEquip
	Item* GetOverItemInEquip();

	// GetID
	DWORD GetID(int _iIndex);

public:
	explicit CInvenWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CInvenWindow();
};
