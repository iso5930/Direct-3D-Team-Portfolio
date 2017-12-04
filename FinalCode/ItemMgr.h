#pragma once

class CItemMgr
{
public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	int m_iGold;

public: ////////////////////////////////////////////////////////////////////////// Share
	int GetGold() { return m_iGold; }

	void SetGold(int _iGold) { m_iGold = _iGold; }

	void Begin();

	void End();

	bool ItemToItem(Item* _pItemA, Item* _pItemB);

	bool SellOfItemInInven(int _iIndex);

	bool SellOfItemInEquip(int _iIndex);

	bool BuyOfItem(Item* _pItem);

private: ////////////////////////////////////////////////////////////////////////// Inventory
	vector<Item*> m_Inventory[2];

public:
	int GetSizeOfInven();

	Item* GetItemInInven(int _iIndex);

	bool FindPosInInven(Item* _pItem);

	void FindItemInInven(vector<int>& _FindIndexVec, Item* _pItem);

	bool AddItemInInven(Item* _pItem);

	bool RemoveItemInInven(int _iIndex);

	int IsEmptyInInven(Item* _pItem);

	bool MoveInInven(int _iIndex, int _iPosX, int _iPosY);

	bool SwapInInven(int _iIndexA, int _iPosX, int _iPosY, int _iIndexB);

	bool DevideInInven(int _iIndex, Item* _pItem);

	bool EnchantInInven(int _iIndexA, int _iIndexB);

	void CommitInven();

	void RollbackInven();

	void ResetInven();

private: ////////////////////////////////////////////////////////////////////////// Equipment
	// 0(Sholders), 1(Helms), 2(Amulet), 3(Gloves), 4(ChestArmor), 5(Bracers)
	// 6(LeftRing), 7(Belt), 8(RightRing), 9(MainWeapon), 10(Pants),
	// 11(SubWeapon), 12(Boots)
	Item* m_pEquipment[2][13];

public:
	int GetSizeOfEquip();

	Item* GetItemInEquip(int _iIndex);

	bool RemoveItemInEquip(int _iIndex);

	bool SetItemInEquip(int _iIndex, Item* _pItem);

	bool MoveInvenToEquip(int _iInvenIndex, int _iEquipIndex);

	bool MoveEquipToInven(int _iEquipIndex, int _iPosX, int _iPosY);

	bool SwapInvenToEquip(int _iInvenIndex, int _iEquipIndex, int _iPosX = -1, int _iPosY = -1);

	bool EnchantInvenToEquip(int _iInvenIndex, int _iEquipIndex);

	bool MoveInEquip(int _iIndexA, int _iIndexB);

	bool SwapInEquip(int _iIndexA, int _iIndexB);

	void CommitEquip();

	void RollbackEquip();

	void ResetEquip();

private: ////////////////////////////////////////////////////////////////////////// Storage
	vector<Item*> m_Storage[2][5];

public:
	int GetSizeOfStorage(int _iPage);

	Item* GetItemInStorage(int _iPage, int _iIndex);

	bool FindPosInStorage(int _iPage, Item* _pItem);

	void FindItemInStorage(vector<int>& _FindIndexVec, int _iPage, Item* _pItem);

	bool AddItemInStorage(int _iPage, Item* _pItem);

	bool RemoveItemInStorage(int _iPage, int _iIndex);

	int IsEmptyInStorage(int _iPage, Item* _pItem);

	bool MoveInStorage(int _iPage, int _iIndex, int _iPosX, int _iPosY);

	bool SwapInStorage(int _iPage, int _iIndexA, int _iPosX, int _iPosY, int _iIndexB);

	bool DevideInStorage(int _iPage, int _iIndex, Item* _pItem);

	bool EnchantInStorage(int _iPage, int _iIndexA, int _iIndexB);

	bool MoveInvenToStorage(int _iInvenIndex, int _iPage, int _iPosX, int _iPosY);

	bool MoveStorageToInven(int _iPage, int _iStorageIndex, int _iPosX, int _iPosY);

	bool SwapInvenToStorage(int _iInvenIndex, int _iPage, int _iStorageIndex, int _iPosX, int _iPosY);

	bool DevideInvenToStorage(int _iInvenIndex, Item* _pItem, int _iPage);

	bool EnchantInvenToStorage(int _iInvenIndex, int _iPage, int _iStorageIndex);

	bool SwapStorageToInven(int _iPage, int _iStorageIndex, int _iInvenIndex, int _iPosX, int _iPosY);

	bool DevideStorageToInven(int _iPage, int _iStorageIndex, Item* _pItem);

	bool EnchantStorageToInven(int _iPage, int _iStorageIndex, int _iInvenIndex);

	bool MoveStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex);

	bool MoveEquipToStorage(int _iEquipIndex, int _iPage, int _iPosX, int _iPosY);

	bool SwapStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex, int _iPosX = -1, int _iPosY = -1);

	bool EnchantStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex);

	void CommitStorage(int _iPage);

	void RollbackStorage(int _iPage);

	void ResetStorage(int _iPage);

private: ////////////////////////////////////////////////////////////////////////// FollowerEquipment
	// 0(MainWeapon), 1(SubWeapon), 2(Amulet), 3(LeftRing), 4(RightRing)
	Item* m_pFollowerEquipment[2][5];

public: 
	int GetSizeOfFollowerEquip();

	Item* GetItemInFollowerEquip(int _iIndex);

	bool RemoveItemInFollowerEquip(int _iIndex);

	bool SetItemInFollowerEquip(int _iIndex, Item* _pItem);

	bool MoveInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex);

	bool SwapInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex, int _iPosX = -1, int _iPosY = -1);

	bool MoveFollowerEquipToInven(int _iFollowerEquipIndex, int _iPosX, int _iPosY);

	bool SwapFollowerEquipToInven(int _iFollowerEquipIndex, int _iInvenIndex, int _iPosX, int _iPosY);

	bool MoveEquipToFollowerEquip(int _iEquipIndex, int _iFollowerEquipIndex);

	bool SwapEquipToFollowerEquip(int _iEquipIndex, int _iFollowerEquipIndex);

	bool MoveFollowerEquipToEquip(int _iFollowerEquipIndex, int _iEquipIndex);

	bool SwapFollowerEquipToEquip(int _iFollowerEquipIndex, int _iEquipIndex);

	bool EnchantInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex);

	bool SwapInFollowerEquip(int _iIndexA, int _iIndexB);

	void CommitFollowerEquip();

	void RollbackFollowerEquip();

	void ResetFollowerEquip();

public: ////////////////////////////////////////////////////////////////////////// Item
	Item* CreateItem(DWORD _dwItemClass, DWORD _dwItemType, DWORD _dwItemID, int _iLevel);

	void CreateName(Item* _pItem);

	void CreateTexKey(Item* _pItem);

	void CreateBufKey(Item* _pItem);

	void CreateSize(Item* _pItem);

	void CreateStat(Item* _pItem);

	void CreateValue(Item* _pItem);

private:
	DECLARE_SINGLETON(CItemMgr)

public:
	explicit CItemMgr();
	~CItemMgr();
};
