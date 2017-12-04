#pragma once

#include "WindowUI.h"

class CStoreButton;
class CStoreSign;

class CStoreWindow : public CWindowUI
{
private:
	// Page
	int m_iPage;

	// Mouse
	CMouse* m_pMouse;

	// Player
	CPlayer* m_pPlayer;

	// StoreButton
	CStoreButton* m_pStoreButton[5];

	// StoreVec
	vector<Item*> m_StoreVec[5];

	// StoreSign
	vector<CStoreSign*> m_StoreSign;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Renew();

public:
	void AddWeapon(Item* _pWeapon);
	void AddArmor(Item* _pArmor);
	void AddAccessory(Item* _pAccessory);
	void SetPuzzleAccessoryLevel(int _iLevel)	{ m_StoreVec[3][0]->iLevel = _iLevel; m_StoreVec[3][0]->iValue = _iLevel * 100; }
	void SetPuzzleBeltLevel(int _iLevel)		{ m_StoreVec[3][1]->iLevel = _iLevel; m_StoreVec[3][1]->iValue = _iLevel * 100; }
	void SetPuzzleBootsLevel(int _iLevel)		{ m_StoreVec[3][2]->iLevel = _iLevel; m_StoreVec[3][2]->iValue = _iLevel * 100; }
	void SetPuzzleBracersLevel(int _iLevel)		{ m_StoreVec[3][3]->iLevel = _iLevel; m_StoreVec[3][3]->iValue = _iLevel * 100; }
	void SetPuzzleChestArmorLevel(int _iLevel)	{ m_StoreVec[3][4]->iLevel = _iLevel; m_StoreVec[3][4]->iValue = _iLevel * 100; }
	void SetPuzzleGlovesLevel(int _iLevel)		{ m_StoreVec[3][5]->iLevel = _iLevel; m_StoreVec[3][5]->iValue = _iLevel * 100; }
	void SetPuzzleHelmLevel(int _iLevel)		{ m_StoreVec[3][6]->iLevel = _iLevel; m_StoreVec[3][6]->iValue = _iLevel * 100; }
	void SetPuzzlePantsLevel(int _iLevel)		{ m_StoreVec[3][7]->iLevel = _iLevel; m_StoreVec[3][7]->iValue = _iLevel * 100; }
	void SetPuzzleShoulderLevel(int _iLevel)	{ m_StoreVec[3][8]->iLevel = _iLevel; m_StoreVec[3][8]->iValue = _iLevel * 100; }
	void SetPuzzleWeaponLevel(int _iLevel)		{ m_StoreVec[3][9]->iLevel = _iLevel; m_StoreVec[3][9]->iValue = _iLevel * 100; }
	void AddRepurchase(Item* _pRepurchase);
	void RemoveRepurchase(int _iIndex);

private:
	////////////////////////////////////////////////////////////////////////// Pick
	void UpdateNonePick();
	void UpdatePick();
	void UpdateInventoryPick();
	void UpdateEquipmentPick();
	void UpdateStorePick();

	////////////////////////////////////////////////////////////////////////// In
	void UpdateIn();
	void UpdateNonePickIn();
	void UpdatePickIn();
	void UpdateInventoryPickIn();
	void UpdateEquipmentPickIn();
	void UpdateStorePickIn();

	////////////////////////////////////////////////////////////////////////// Out
	void UpdateOut();
	void UpdateNonePickOut();
	void UpdatePickOut();
	void UpdateInventoryPickOut();
	void UpdateEquipmentPickOut();
	void UpdateStorePickOut();

	////////////////////////////////////////////////////////////////////////// InStore
	void UpdateInStore();
	void UpdateNonePickInStore();
	void UpdatePickInStore();
	void UpdateInventoryPickInStore();
	void UpdateEquipmentPickInStore();
	void UpdateStorePickInStore();

public:
	explicit CStoreWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CStoreWindow();
};
