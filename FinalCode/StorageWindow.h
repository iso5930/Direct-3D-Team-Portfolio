#pragma once

#include "WindowUI.h"

class CStorageButton;
class CGridSign;
class CBasicSign;

class CStorageWindow : public CWindowUI
{
private:
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

	// Page
	int m_iPage;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// StorageButton
	CStorageButton* m_pStorageButton[5];

	// StorageSign
	vector<CItemSign*> m_StorageSign;

	// BorderSign
	CBasicSign* m_pBorderSign[3];

	/*
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
	*/

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Renew();

public:
	// GetPage
	int GetPage() { return m_iPage; }

private:
	////////////////////////////////////////////////////////////////////////// Pick
	void UpdateNonePick();
	void UpdatePick();
	void UpdateInventoryPick();
	void UpdateEquipmentPick();
	void UpdateStoragePick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateInventoryPickIn();
	void UpdateEquipmentPickIn();
	void UpdateStoragePickIn();

	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateInventoryPickOut();
	void UpdateEquipmentPickOut();
	void UpdateStoragePickOut();

	////////////////////////////////////////////////////////////////////////// InStorage
	void UpdateInStorage();
	void UpdateNonePickInStorage();
	void UpdatePickInStorage();
	void UpdateInventoryPickInStorage();
	void UpdateEquipmentPickInStorage();
	void UpdateStoragePickInStorage();

public:
	// GetOverItemInStorage
	Item* GetOverItemInStorage();

public:
	explicit CStorageWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CStorageWindow();
};
