#include "StdAfx.h"
#include "ItemMgr.h"

IMPLEMENT_SINGLETON(CItemMgr)

CItemMgr::CItemMgr()
{
	// Equipment
	ZeroMemory(m_pEquipment[0], sizeof(m_pEquipment[0]));
	ZeroMemory(m_pEquipment[1], sizeof(m_pEquipment[1]));
	
	// FollowerEquipment
	ZeroMemory(m_pFollowerEquipment[0], sizeof(m_pFollowerEquipment[0]));
	ZeroMemory(m_pFollowerEquipment[1], sizeof(m_pFollowerEquipment[1]));

	CommitInven();
	CommitEquip();
	CommitStorage(0);
	CommitStorage(1);
	CommitStorage(2);
	CommitStorage(3);
	CommitStorage(4);
	CommitFollowerEquip();
}

CItemMgr::~CItemMgr()
{
	Release();
}

void CItemMgr::Initialize()
{
}

int CItemMgr::Update()
{
	return 0;
}

void CItemMgr::Render()
{
}

void CItemMgr::Release()
{
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
	{
		delete m_Inventory[0][i];
		m_Inventory[0][i] = NULL;
	}
	m_Inventory[0].clear();
	CommitInven();

	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
		{
			delete m_pEquipment[0][i];
			m_pEquipment[0][i] = NULL;
		}
	}
	CommitEquip();

	for(int i = 0; i < 5; ++i)
	{
		for(size_t j = 0; j < m_Storage[0][i].size(); ++j)
		{
			delete m_Storage[0][i][j];
			m_Storage[0][i][j] = NULL;
		}
		m_Storage[0][i].clear();
		CommitStorage(i);
	}

	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[0][i] != NULL)
		{
			delete m_pFollowerEquipment[0][i];
			m_pFollowerEquipment[0][i] = NULL;
		}
	}
	CommitFollowerEquip();
}

////////////////////////////////////////////////////////////////////////// Share
void CItemMgr::Begin()
{
	// Gold
	m_iGold = CDataMgr::GetInstance()->GetGold();

	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

	for(int i = 0; i < pAccount->iItemNum; ++i)
	{
		Item* pItem = new Item(pAccount->ItemVec[i]);
		AddItemInInven(pItem);
	}
	CommitInven();

	for(int i = 0; i < pAccount->iEquipNum; ++i)
	{
		Item* pItem = new Item(pAccount->EquipVec[i]);
		SetItemInEquip(pAccount->EquipIndexVec[i], pItem);
	}
	CommitEquip();

	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < pAccount->iStorageNum[i]; ++j)
		{
			Item* pItem = new Item(pAccount->StorageVec[i][j]);
			AddItemInStorage(i, pItem);
		}
		CommitStorage(i);
	}

	for(int i = 0; i < pAccount->iFollowerEquipNum; ++i)
	{
		Item* pItem = new Item(pAccount->FollowerEquipVec[i]);
		SetItemInFollowerEquip(pAccount->FollowerEquipIndexVec[i], pItem);
	}
	CommitFollowerEquip();
}

void CItemMgr::End()
{
	m_iGold = 0;

	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
	{
		delete m_Inventory[0][i];
		m_Inventory[0][i] = NULL;
	}
	m_Inventory[0].clear();
	CommitInven();

	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
		{
			delete m_pEquipment[0][i];
			m_pEquipment[0][i] = NULL;
		}
	}
	CommitEquip();

	for(int i = 0; i < 5; ++i)
	{
		for(size_t j = 0; j < m_Storage[0][i].size(); ++j)
		{
			delete m_Storage[0][i][j];
			m_Storage[0][i][j] = NULL;
		}
		m_Storage[0][i].clear();
		CommitStorage(i);
	}
}

bool CItemMgr::ItemToItem(Item* _pItemA, Item* _pItemB)
{
	if(_pItemA->iPosX + _pItemA->iWidth > _pItemB->iPosX && _pItemA->iPosX < _pItemB->iPosX + _pItemB->iWidth && _pItemA->iPosY + _pItemA->iHeight > _pItemB->iPosY && _pItemA->iPosY < _pItemB->iPosY + _pItemB->iHeight)
		return true;

	return false;
}

bool CItemMgr::SellOfItemInInven(int _iIndex)
{
	m_iGold += (m_Inventory[0][_iIndex]->iValue * m_Inventory[0][_iIndex]->iNum / 10);
	RemoveItemInInven(_iIndex);
	return true;
}

bool CItemMgr::SellOfItemInEquip(int _iIndex)
{
	m_iGold += (m_pEquipment[0][_iIndex]->iValue * m_pEquipment[0][_iIndex]->iNum / 10);
	RemoveItemInEquip(_iIndex);
	return true;
}

bool CItemMgr::BuyOfItem(Item* _pItem)
{
	Item* pItem;

	if(_pItem->dwItemClass & ITEM_CLASS_PUZZLE)
	{
		int iRand = rand() % 100;
		DWORD dwItemClass = ITEM_CLASS_NORMAL;
		if(iRand > 95)
			dwItemClass = ITEM_CLASS_SET;
		else if(iRand > 85)
			dwItemClass = ITEM_CLASS_LEGEND;
		else if(iRand > 70)
			dwItemClass = ITEM_CLASS_UNIQUE;
		else if(iRand > 55)
			dwItemClass = ITEM_CLASS_MAGIC;

		if(_pItem->dwItemID & (ITEM_TYPE_AMULET | ITEM_TYPE_RING))
		{
			iRand = rand() % 2;
			if(iRand == 0)
				pItem = CreateItem(dwItemClass, ITEM_TYPE_AMULET, 0, _pItem->iLevel);
			else
				pItem = CreateItem(dwItemClass, ITEM_TYPE_RING, 0, _pItem->iLevel);
		}
		else if(_pItem->dwItemID & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON))
		{
			iRand = rand() % 2;
			if(iRand == 0)
				pItem = CreateItem(dwItemClass, ITEM_TYPE_MAIN_WEAPON, 0, _pItem->iLevel);
			else
				pItem = CreateItem(dwItemClass, ITEM_TYPE_SUB_WEAPON, 0, _pItem->iLevel);
		}
		else
			pItem = CreateItem(dwItemClass, _pItem->dwItemType, 0, _pItem->iLevel);
	}
	else
		pItem = new Item(_pItem);

	pItem->iPosX = -1;
	pItem->iPosY = -1;

	if(AddItemInInven(pItem) == false)
	{
		delete pItem;
		return false;
	}

	m_iGold -= _pItem->iValue * _pItem->iNum;
	return true;
}

////////////////////////////////////////////////////////////////////////// Inventory
int CItemMgr::GetSizeOfInven()
{
	return m_Inventory[0].size();
}

Item* CItemMgr::GetItemInInven(int _iIndex)
{
	if(_iIndex >= m_Inventory[0].size())
		return NULL;

	return m_Inventory[0][_iIndex];
}

bool CItemMgr::FindPosInInven(Item* _pItem)
{
	for(int i = 0; i < 10; ++i)
	{
		_pItem->iPosX = i;
		if(_pItem->iPosX + _pItem->iWidth > 10)
			continue;

		for(int j = 0; j < 6; ++j)
		{
			_pItem->iPosY = j;
			if(_pItem->iPosY + _pItem->iHeight > 6)
				continue;

			if(IsEmptyInInven(_pItem) == 0)
				return true;
		}
	}

	return false;
}

void CItemMgr::FindItemInInven(vector<int>& _FindIndexVec, Item* _pItem)
{
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
	{
		if((_pItem->dwItemType & m_Inventory[0][i]->dwItemType) && (_pItem->dwItemID & m_Inventory[0][i]->dwItemID))
			_FindIndexVec.push_back(i);
	}
}

bool CItemMgr::AddItemInInven(Item* _pItem)
{
	if(_pItem->dwItemType & ITEM_TYPE_GOLD)
	{
		m_iGold += _pItem->iValue;
		delete _pItem;
		return true;
	}

	if(_pItem->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		// FindIndexVec
		vector<int> FindIndexVec;
		FindItemInInven(FindIndexVec, _pItem);
		
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			if(m_Inventory[0][FindIndexVec[i]]->iPosX == _pItem->iPosX && m_Inventory[0][FindIndexVec[i]]->iPosY == _pItem->iPosY)
			{
				m_Inventory[0][FindIndexVec[i]]->iNum += _pItem->iNum;
				delete _pItem;
				return true;
			}
		}

		if(FindIndexVec.size() != 0 && _pItem->iPosX == -1 && _pItem->iPosY == -1)
		{
			m_Inventory[0][FindIndexVec[0]]->iNum += _pItem->iNum;
			delete _pItem;
			return true;
		}

		if(FindIndexVec.size() != 0 && _pItem->iPosX >= 0 && _pItem->iPosX + _pItem->iWidth <= 10 && _pItem->iPosY >= 0 && _pItem->iPosY + _pItem->iHeight <= 6)
		{
			if(IsEmptyInInven(_pItem) > 0)
			{
				m_Inventory[0][FindIndexVec[0]]->iNum += _pItem->iNum;
				delete _pItem;
				return true;
			}
		}
	}

	if(_pItem->iPosX >= 0 && _pItem->iPosX + _pItem->iWidth <= 10 && _pItem->iPosY >= 0 && _pItem->iPosY + _pItem->iHeight <= 6)
	{
		if(IsEmptyInInven(_pItem) == 0)
		{
			m_Inventory[0].push_back(_pItem);
			return true;
		}
	}

	if(FindPosInInven(_pItem))
	{
		m_Inventory[0].push_back(_pItem);
		return true;
	}

	return false;
}

bool CItemMgr::RemoveItemInInven(int _iIndex)
{
	if(_iIndex >= m_Inventory[0].size())
		return false;

	delete m_Inventory[0][_iIndex];
	m_Inventory[0][_iIndex] = m_Inventory[0].back();
	m_Inventory[0].pop_back();
	return true;
}

int CItemMgr::IsEmptyInInven(Item* _pItem)
{
	int iCnt = 0;
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
	{
		if(ItemToItem(_pItem, m_Inventory[0][i]))
			++iCnt;
	}
	return iCnt;
}

bool CItemMgr::MoveInInven(int _iIndex, int _iPosX, int _iPosY)
{
	// Pos
	m_Inventory[0][_iIndex]->iPosX = _iPosX;
	m_Inventory[0][_iIndex]->iPosY = _iPosY;

	return true;
}

bool CItemMgr::SwapInInven(int _iIndexA, int _iPosX, int _iPosY, int _iIndexB)
{
	// Accumulate
	if(m_Inventory[0][_iIndexA]->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		if((m_Inventory[0][_iIndexA]->dwItemType & m_Inventory[0][_iIndexB]->dwItemType) && (m_Inventory[0][_iIndexA]->dwItemID & m_Inventory[0][_iIndexB]->dwItemID))
		{
			m_Inventory[0][_iIndexB]->iNum += m_Inventory[0][_iIndexA]->iNum;
			RemoveItemInInven(_iIndexA);
			return true;
		}
	}

	// Item
	Item* pItemA = new Item(m_Inventory[0][_iIndexA]);
	Item* pItemB = new Item(m_Inventory[0][_iIndexB]);

	// RemoveItem
	if(_iIndexA > _iIndexB)
	{
		RemoveItemInInven(_iIndexA);
		RemoveItemInInven(_iIndexB);
	}
	else
	{
		RemoveItemInInven(_iIndexB);
		RemoveItemInInven(_iIndexA);
	}

	// Pos
	pItemB->iPosX = pItemA->iPosX;
	pItemB->iPosY = pItemA->iPosY;
	pItemA->iPosX = _iPosX;
	pItemA->iPosY = _iPosY;

	// AddItemA
	if(AddItemInInven(pItemA) == false)
	{
		delete pItemA;
		delete pItemB;
		return false;
	}

	// AddItemB
	if(AddItemInInven(pItemB) == false)
	{
		delete pItemB;
		return false;
	}

	return true;
}

bool CItemMgr::DevideInInven(int _iIndex, Item* _pItem)
{
	// Item
	Item* pItem = new Item(_pItem);

	// Num
	m_Inventory[0][_iIndex]->iNum -= pItem->iNum;

	// AddItemInInven
	if(AddItemInInven(pItem))
		return true;

	delete pItem;
	return false;
}

bool CItemMgr::EnchantInInven(int _iIndexA, int _iIndexB)
{
	// Check Sock
	if(m_Inventory[0][_iIndexB]->iSockNum == m_Inventory[0][_iIndexB]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Inventory[0][_iIndexA]);
	pGem->iNum = 1;
	m_Inventory[0][_iIndexB]->SockArr[m_Inventory[0][_iIndexB]->iSockCnt++] = pGem;

	if(m_Inventory[0][_iIndexA]->iNum == 1)
		RemoveItemInInven(_iIndexA);
	else
		m_Inventory[0][_iIndexA]->iNum -= 1;

	return true;
}

void CItemMgr::CommitInven()
{
	// Clear
	for(size_t i = 0; i < m_Inventory[1].size(); ++i)
		delete m_Inventory[1][i];
	m_Inventory[1].clear();

	// Copy
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
	{
		Item* pItem = new Item(m_Inventory[0][i]);
		m_Inventory[1].push_back(pItem);
	}
}

void CItemMgr::RollbackInven()
{
	// Clear
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
		delete m_Inventory[0][i];
	m_Inventory[0].clear();

	// Copy
	for(size_t i = 0; i < m_Inventory[1].size(); ++i)
	{
		Item* pItem = new Item(m_Inventory[1][i]);
		m_Inventory[0].push_back(pItem);
	}
}

void CItemMgr::ResetInven()
{
	for(size_t i = 0; i < m_Inventory[0].size(); ++i)
		delete m_Inventory[0][i];
	m_Inventory[0].clear();

	for(size_t i = 0; i < m_Inventory[1].size(); ++i)
		delete m_Inventory[1][i];
	m_Inventory[1].clear();
}

////////////////////////////////////////////////////////////////////////// Equipment
int CItemMgr::GetSizeOfEquip()
{
	int iCnt = 0;
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
			++iCnt;
	}

	return iCnt;
}

Item* CItemMgr::GetItemInEquip(int _iIndex)
{
	if(_iIndex >= 13)
		return NULL;

	return m_pEquipment[0][_iIndex];
}

bool CItemMgr::SetItemInEquip(int _iIndex, Item* _pItem)
{
	if(_iIndex >= 13)
		return false;

	if(m_pEquipment[0][_iIndex] != NULL)
		return false;

	m_pEquipment[0][_iIndex] = _pItem;
	return true;
}

bool CItemMgr::RemoveItemInEquip(int _iIndex)
{
	if(_iIndex >= 13)
		return false;

	if(m_pEquipment[0][_iIndex] == NULL)
		return false;

	delete m_pEquipment[0][_iIndex];
	m_pEquipment[0][_iIndex] = NULL;
	return true;
}

bool CItemMgr::MoveInvenToEquip(int _iInvenIndex, int _iEquipIndex)
{
	// TempItem
	Item* pTempItem = NULL;
	if(_iEquipIndex == 9 && m_pEquipment[0][11] != NULL)
	{
		// 왼쪽이 한손도끼일 때,
		if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 활일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_BOW)
		{
			// 왼쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 의식용칼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 왼쪽이 주먹무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_FIST)
		{
		}
		// 왼쪽이 손쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
		}
		// 왼쪽이 철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 오른쪽이 손쇠뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 화살통일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 왼쪽이 거대한손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
		}
		// 왼쪽이 거대두손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 방패일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
		}
		// 왼쪽이 창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 지팡이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_STAFF)
		{
			// 오른쪽이 방패, 오브, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손도끼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 완드일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 왼쪽이 액막이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MOJO)
		{
		}
		// 왼쪽이 쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 오브일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_ORB)
		{
		}
	}

	if(_iEquipIndex == 11 && m_pEquipment[0][9] != NULL)
	{
		// 오른쪽이 한손도끼일 때,
		if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 활일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_BOW)
		{
		}
		// 오른쪽이 의식용칼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 오른쪽이 주먹무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_FIST)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 손쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
			// 왼쪽이 손쇠뇌가 아니면 해제한다.
			if(false == (m_pEquipment[0][9]->dwItemID & WEAPON_ID_HANDXBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 양손창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
		}
		// 오른쪽이 화살통일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 오른쪽이 거대한손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 거대두손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
		}
		// 오른쪽이 방패일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 지팡이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_STAFF)
		{
		}
		// 오른쪽이 검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손도끼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
		}
		// 오른쪽이 두손철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
		}
		// 오른쪽이 두손검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
		}
		// 오른쪽이 완드일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 오른쪽이 액막이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MOJO)
		{
			// 왼쪽이 양손창, 양손도끼, 양손철퇴, 양손검, 스태프, 활, 석궁이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_STAFF | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
		}
		// 오른쪽이 오브일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_ORB)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
	}

	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pInvenItem) == false)
	{
		delete pInvenItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInInven
	if(pTempItem != NULL)
	{
		if(AddItemInInven(pTempItem) == false)
		{
			delete pTempItem;
			return false;
		}
	}

	// Sort
	if(m_pEquipment[0][9] == NULL && m_pEquipment[0][11] != NULL && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		m_pEquipment[0][9] = m_pEquipment[0][11];
		m_pEquipment[0][11] = NULL;
	}

	return true;
}

bool CItemMgr::MoveEquipToInven(int _iEquipIndex, int _iPosX, int _iPosY)
{
	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	RemoveItemInEquip(_iEquipIndex);

	// AddItemInInven
	pEquipItem->iPosX = _iPosX;
	pEquipItem->iPosY = _iPosY;
	AddItemInInven(pEquipItem);

	return true;
}

bool CItemMgr::SwapInvenToEquip(int _iInvenIndex, int _iEquipIndex, int _iPosX /*= -1*/, int _iPosY /*= -1*/)
{
	// TempItem
	Item* pTempItem = NULL;
	if(_iEquipIndex == 9 && m_pEquipment[0][11] != NULL)
	{
		// 왼쪽이 한손도끼일 때,
		if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 활일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_BOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 의식용칼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 왼쪽이 주먹무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_FIST)
		{
		}
		// 왼쪽이 손쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
		}
		// 왼쪽이 철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 화살통일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 왼쪽이 거대한손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
		}
		// 왼쪽이 거대두손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 방패일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
		}
		// 왼쪽이 창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 오른쪽이 손쇠뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 지팡이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_STAFF)
		{
			// 오른쪽이 방패, 오브, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 오른쪽이 손쇠뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손도끼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 양손검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 완드일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 왼쪽이 액막이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MOJO)
		{
		}
		// 왼쪽이 쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 오브일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_ORB)
		{
		}
	}

	if(_iEquipIndex == 11 && m_pEquipment[0][9] != NULL)
	{
		// 오른쪽이 한손도끼일 때,
		if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 활일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_BOW)
		{
		}
		// 오른쪽이 의식용칼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 오른쪽이 주먹무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_FIST)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 손쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
			// 왼쪽이 손쇠뇌가 아니면 해제한다.
			if(false == (m_pEquipment[0][9]->dwItemID & WEAPON_ID_HANDXBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 양손창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
		}
		// 오른쪽이 화살통일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 오른쪽이 거대한손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
		}
		// 오른쪽이 거대양손무기일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
		}
		// 오른쪽이 방패일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 양손도끼, 양손철퇴, 양손검, 양손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 창일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 지팡이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_STAFF)
		{
		}
		// 오른쪽이 검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손도끼일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
		}
		// 오른쪽이 두손철퇴일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
		}
		// 오른쪽이 두손검일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
		}
		// 오른쪽이 완드일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 오른쪽이 액막이일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_MOJO)
		{
			// 왼쪽이 양손창, 양손도끼, 양손철퇴, 양손검, 스태프, 활, 석궁이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_STAFF | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 쇠뇌일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
		}
		// 오른쪽이 오브일 때,
		else if(m_Inventory[0][_iInvenIndex]->dwItemID & WEAPON_ID_ORB)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
	}

	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	pEquipItem->iPosX = (_iPosX == -1 ? pInvenItem->iPosX : _iPosX);
	pEquipItem->iPosY = (_iPosY == -1 ? pInvenItem->iPosY : _iPosY);
	RemoveItemInEquip(_iEquipIndex);

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pInvenItem) == false)
	{
		delete pInvenItem;
		delete pEquipItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInInven
	if(AddItemInInven(pEquipItem) == false)
	{
		delete pEquipItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInInven
	if(pTempItem != NULL)
	{
		if(AddItemInInven(pTempItem) == false)
		{
			delete pTempItem;
			return false;
		}
	}

	// Sort
	if(m_pEquipment[0][9] == NULL && m_pEquipment[0][11] != NULL && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		m_pEquipment[0][9] = m_pEquipment[0][11];
		m_pEquipment[0][11] = NULL;
	}

	return true;
}

bool CItemMgr::EnchantInvenToEquip(int _iInvenIndex, int _iEquipIndex)
{
	// Check Sock
	if(m_pEquipment[0][_iEquipIndex]->iSockNum == m_pEquipment[0][_iEquipIndex]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Inventory[0][_iInvenIndex]);
	pGem->iNum = 1;
	m_pEquipment[0][_iEquipIndex]->SockArr[m_pEquipment[0][_iEquipIndex]->iSockCnt++] = pGem;

	if(m_Inventory[0][_iInvenIndex]->iNum == 1)
		RemoveItemInInven(_iInvenIndex);
	else
		m_Inventory[0][_iInvenIndex]->iNum -= 1;

	return true;
}

bool CItemMgr::MoveInEquip(int _iIndexA, int _iIndexB)
{
	if(_iIndexA == _iIndexB)
		return true;

	m_pEquipment[0][_iIndexB] = m_pEquipment[0][_iIndexA];
	m_pEquipment[0][_iIndexA] = NULL;

	return true;
}

bool CItemMgr::SwapInEquip(int _iIndexA, int _iIndexB)
{
	if(_iIndexA == _iIndexB)
		return true;

	// A가 도끼일 때,
	if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_AXE)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 활일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_BOW)
	{
	}
	// A가 의식용칼일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_CEREMONIAL_DAGGER)
	{
	}
	// A가 주먹무기일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_FIST)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 손쇠뇌일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_HANDXBOW)
	{
		// B가 화살통, 방패이면 실패한다.
		DWORD dw = WEAPON_ID_QUIVER | WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 철퇴일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_MACE)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 두손창일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_POLEARM)
	{
	}
	// A가 화살통일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_QUIVER)
	{
		// B가 손쇠뇌면 실패한다.
		DWORD dw = WEAPON_ID_HANDXBOW;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 한손거대무기일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_MIGHTY1H)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 두손거대무기일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_MIGHTY2H)
	{
	}
	// A가 방패일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_SHIELD)
	{
	}
	// A가 창일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_SPEAR)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 지팡이일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_STAFF)
	{
	}
	// A가 검일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_SWORD)
	{
		// B가 방패이면 실패한다.
		DWORD dw = WEAPON_ID_SHIELD;
		if(m_pEquipment[0][_iIndexB]->dwItemID & dw)
			return false;
	}
	// A가 두손도끼일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_TWO_HAND_AXE)
	{
	}
	// A가 두손철퇴일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_TWO_HAND_MACE)
	{
	}
	// A가 두손검일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_TWO_HAND_SWORD)
	{
	}
	// A가 완드일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_WAND)
	{
	}
	// A가 액막이일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_MOJO)
	{
	}
	// A가 쇠뇌일 때,
	if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_CROSSBOW)
	{
	}
	// A가 오브일 때,
	else if(m_pEquipment[0][_iIndexA]->dwItemID &WEAPON_ID_ORB)
	{
	}

	Item* pTemp = m_pEquipment[0][_iIndexA];
	m_pEquipment[0][_iIndexA] = m_pEquipment[0][_iIndexB];
	m_pEquipment[0][_iIndexB] = pTemp;

	return true;
}

void CItemMgr::CommitEquip()
{
	// Clear
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[1][i] != NULL)
		{
			delete m_pEquipment[1][i];
			m_pEquipment[1][i] = NULL;
		}
	}

	// Copy
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
			m_pEquipment[1][i] = new Item(m_pEquipment[0][i]);
	}
}

void CItemMgr::RollbackEquip()
{
	// Clear
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
		{
			delete m_pEquipment[0][i];
			m_pEquipment[0][i] = NULL;
		}
	}

	// Copy
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[1][i] != NULL)
			m_pEquipment[0][i] = new Item(m_pEquipment[1][i]);
	}
}

void CItemMgr::ResetEquip()
{
	for(int i = 0; i < 13; ++i)
	{
		if(m_pEquipment[0][i] != NULL)
		{
			delete m_pEquipment[0][i];
			m_pEquipment[0][i] = NULL;
		}

		if(m_pEquipment[1][i] != NULL)
		{
			delete m_pEquipment[1][i];
			m_pEquipment[1][i] = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////// Storage
int CItemMgr::GetSizeOfStorage(int _iPage)
{
	return m_Storage[0][_iPage].size();
}

Item* CItemMgr::GetItemInStorage(int _iPage, int _iIndex)
{
	return m_Storage[0][_iPage][_iIndex];
}

bool CItemMgr::FindPosInStorage(int _iPage, Item* _pItem)
{
	for(int i = 0; i < 7; ++i)
	{
		_pItem->iPosX = i;
		if(_pItem->iPosX + _pItem->iWidth > 7)
			continue;

		for(int j = 0; j < 10; ++j)
		{
			_pItem->iPosY = j;
			if(_pItem->iPosY + _pItem->iHeight > 10)
				continue;

			if(IsEmptyInStorage(_iPage, _pItem) == 0)
				return true;
		}
	}

	return false;
}

void CItemMgr::FindItemInStorage(vector<int>& _FindIndexVec, int _iPage, Item* _pItem)
{
	for(size_t i = 0; i < m_Storage[0][_iPage].size(); ++i)
	{
		if((_pItem->dwItemType & m_Storage[0][_iPage][i]->dwItemType) && (_pItem->dwItemID & m_Storage[0][_iPage][i]->dwItemID))
			_FindIndexVec.push_back(i);
	}
}

bool CItemMgr::AddItemInStorage(int _iPage, Item* _pItem)
{
	if(_pItem->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		// FindIndexVec
		vector<int> FindIndexVec;
		FindItemInStorage(FindIndexVec, _iPage, _pItem);

		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			if(m_Storage[0][_iPage][FindIndexVec[i]]->iPosX == _pItem->iPosX && m_Storage[0][_iPage][FindIndexVec[i]]->iPosY == _pItem->iPosY)
			{
				m_Storage[0][_iPage][FindIndexVec[i]]->iNum += _pItem->iNum;
				delete _pItem;
				return true;
			}
		}

		if(FindIndexVec.size() != 0 && _pItem->iPosX == -1 && _pItem->iPosY == -1)
		{
			m_Storage[0][_iPage][FindIndexVec[0]]->iNum += _pItem->iNum;
			delete _pItem;
			return true;
		}

		if(FindIndexVec.size() != 0&& _pItem->iPosX >= 0 && _pItem->iPosX + _pItem->iWidth <= 7 && _pItem->iPosY >= 0 && _pItem->iPosY + _pItem->iHeight <= 10)
		{
			if(IsEmptyInStorage(_iPage, _pItem) > 0)
			{
				m_Storage[0][_iPage][FindIndexVec[0]]->iNum += _pItem->iNum;
				delete _pItem;
				return true;
			}
		}
	}

	if(_pItem->iPosX >= 0 && _pItem->iPosX + _pItem->iWidth <= 7 && _pItem->iPosY >= 0 && _pItem->iPosY + _pItem->iHeight <= 10)
	{
		if(IsEmptyInStorage(_iPage, _pItem) == 0)
		{
			m_Storage[0][_iPage].push_back(_pItem);
			return true;
		}
	}

	if(FindPosInStorage(_iPage, _pItem))
	{
		m_Storage[0][_iPage].push_back(_pItem);
		return true;
	}

	return false;
}

bool CItemMgr::RemoveItemInStorage(int _iPage, int _iIndex)
{
	if(_iIndex >= m_Storage[0][_iPage].size())
		return false;

	delete m_Storage[0][_iPage][_iIndex];
	m_Storage[0][_iPage][_iIndex] = m_Storage[0][_iPage].back();
	m_Storage[0][_iPage].pop_back();
	return true;
}

int CItemMgr::IsEmptyInStorage(int _iPage, Item* _pItem)
{
	int iCnt = 0;
	for(size_t i = 0; i < m_Storage[0][_iPage].size(); ++i)
	{
		if(ItemToItem(_pItem, m_Storage[0][_iPage][i]))
			++iCnt;
	}
	return iCnt;
}

bool CItemMgr::MoveInStorage(int _iPage, int _iIndex, int _iPosX, int _iPosY)
{
	m_Storage[0][_iPage][_iIndex]->iPosX = _iPosX;
	m_Storage[0][_iPage][_iIndex]->iPosY = _iPosY;
	return true;
}

bool CItemMgr::SwapInStorage(int _iPage, int _iIndexA, int _iPosX, int _iPosY, int _iIndexB)
{
	// Accumulate
	if(m_Storage[0][_iPage][_iIndexA]->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		if((m_Storage[0][_iPage][_iIndexA]->dwItemType & m_Storage[0][_iPage][_iIndexB]->dwItemType) && (m_Storage[0][_iPage][_iIndexA]->dwItemID & m_Storage[0][_iPage][_iIndexB]->dwItemID))
		{
			m_Storage[0][_iPage][_iIndexB]->iNum += m_Storage[0][_iPage][_iIndexA]->iNum;
			RemoveItemInStorage(_iPage, _iIndexA);
			return true;
		}
	}

	// Item
	Item* pItemA = new Item(m_Storage[0][_iPage][_iIndexA]);
	Item* pItemB = new Item(m_Storage[0][_iPage][_iIndexB]);

	// RemoveItem
	if(_iIndexA > _iIndexB)
	{
		RemoveItemInStorage(_iPage, _iIndexA);
		RemoveItemInStorage(_iPage, _iIndexB);
	}
	else
	{
		RemoveItemInStorage(_iPage, _iIndexB);
		RemoveItemInStorage(_iPage, _iIndexA);
	}

	// Pos
	pItemB->iPosX = pItemA->iPosX;
	pItemB->iPosY = pItemA->iPosY;
	pItemA->iPosX = _iPosX;
	pItemA->iPosY = _iPosY;

	// AddItemA
	if(AddItemInStorage(_iPage, pItemA) == false)
	{
		delete pItemA;
		delete pItemB;
		return false;
	}

	// AddItemB
	if(AddItemInStorage(_iPage, pItemB) == false)
	{
		delete pItemB;
		return false;
	}

	return true;
}

bool CItemMgr::DevideInStorage(int _iPage, int _iIndex, Item* _pItem)
{
	// Item
	Item* pItem = new Item(_pItem);

	// Num
	m_Storage[0][_iPage][_iIndex]->iNum -= pItem->iNum;

	// AddItemInStorage
	if(AddItemInStorage(_iPage, pItem))
		return true;

	delete pItem;
	return false;
}

bool CItemMgr::EnchantInStorage(int _iPage, int _iIndexA, int _iIndexB)
{
	// Check Sock
	if(m_Storage[0][_iPage][_iIndexB]->iSockNum == m_Storage[0][_iPage][_iIndexB]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Storage[0][_iPage][_iIndexA]);
	pGem->iNum = 1;
	m_Storage[0][_iPage][_iIndexB]->SockArr[m_Storage[0][_iPage][_iIndexB]->iSockCnt++] = pGem;

	if(m_Storage[0][_iPage][_iIndexA]->iNum == 1)
		RemoveItemInStorage(_iPage, _iIndexA);
	else
		m_Storage[0][_iPage][_iIndexA]->iNum -= 1;

	return true;
}

bool CItemMgr::MoveInvenToStorage(int _iInvenIndex, int _iPage, int _iPosX, int _iPosY)
{
	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// AddItemInStorage
	pInvenItem->iPosX = _iPosX;
	pInvenItem->iPosY = _iPosY;
	if(AddItemInStorage(_iPage, pInvenItem) == false)
	{
		delete pInvenItem;
		return false;
	}

	return true;
}

bool CItemMgr::MoveStorageToInven(int _iPage, int _iStorageIndex, int _iPosX, int _iPosY)
{
	// StorageItem
	Item* pStorageItem = new Item(m_Storage[0][_iPage][_iStorageIndex]);
	RemoveItemInStorage(_iPage, _iStorageIndex);

	// AddItemInInven
	pStorageItem->iPosX = _iPosX;
	pStorageItem->iPosY = _iPosY;
	if(AddItemInInven(pStorageItem) == false)
	{
		delete pStorageItem;
		return false;
	}

	return true;
}

bool CItemMgr::SwapInvenToStorage(int _iInvenIndex, int _iPage, int _iStorageIndex, int _iPosX, int _iPosY)
{
	// Accumulate
	if(m_Inventory[0][_iInvenIndex]->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		if((m_Storage[0][_iPage][_iStorageIndex]->dwItemType & m_Inventory[0][_iInvenIndex]->dwItemType) && (m_Storage[0][_iPage][_iStorageIndex]->dwItemID & m_Inventory[0][_iInvenIndex]->dwItemID))
		{
			m_Storage[0][_iPage][_iStorageIndex]->iNum += m_Inventory[0][_iInvenIndex]->iNum;
			RemoveItemInInven(_iInvenIndex);
			return true;
		}
	}

	// Item
	Item* pItemA = new Item(m_Inventory[0][_iInvenIndex]);
	Item* pItemB = new Item(m_Storage[0][_iPage][_iStorageIndex]);

	// RemoveItem
	RemoveItemInInven(_iInvenIndex);
	RemoveItemInStorage(_iPage, _iStorageIndex);

	// Pos
	pItemB->iPosX = pItemA->iPosX;
	pItemB->iPosY = pItemA->iPosY;
	pItemA->iPosX = _iPosX;
	pItemA->iPosY = _iPosY;

	// AddItemA
	if(AddItemInStorage(_iPage, pItemA) == false)
	{
		delete pItemA;
		delete pItemB;
		return false;
	}

	// AddItemB
	if(AddItemInInven(pItemB) == false)
	{
		delete pItemB;
		return false;
	}

	return true;
}

bool CItemMgr::DevideInvenToStorage(int _iInvenIndex, Item* _pItem, int _iPage)
{
	// Item
	Item* pItem = new Item(_pItem);

	// Num
	m_Inventory[0][_iInvenIndex]->iNum -= pItem->iNum;

	// AddItemInInven
	if(AddItemInStorage(_iPage, pItem))
		return true;

	delete pItem;
	return false;
}

bool CItemMgr::EnchantInvenToStorage(int _iInvenIndex, int _iPage, int _iStorageIndex)
{
	// Check Sock
	if(m_Storage[0][_iPage][_iStorageIndex]->iSockNum == m_Storage[0][_iPage][_iStorageIndex]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Inventory[0][_iInvenIndex]);
	pGem->iNum = 1;
	m_Storage[0][_iPage][_iStorageIndex]->SockArr[m_Storage[0][_iPage][_iStorageIndex]->iSockCnt++] = pGem;

	if(m_Inventory[0][_iInvenIndex]->iNum == 1)
		RemoveItemInInven(_iInvenIndex);
	else
		m_Inventory[0][_iInvenIndex]->iNum -= 1;

	return true;
}

bool CItemMgr::SwapStorageToInven(int _iPage, int _iStorageIndex, int _iInvenIndex, int _iPosX, int _iPosY)
{
	// Accumulate
	if(m_Storage[0][_iPage][_iStorageIndex]->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		if((m_Storage[0][_iPage][_iStorageIndex]->dwItemType & m_Inventory[0][_iInvenIndex]->dwItemType) && (m_Storage[0][_iPage][_iStorageIndex]->dwItemID & m_Inventory[0][_iInvenIndex]->dwItemID))
		{
			m_Inventory[0][_iInvenIndex]->iNum += m_Storage[0][_iPage][_iStorageIndex]->iNum;
			RemoveItemInStorage(_iPage, _iStorageIndex);
			return true;
		}
	}

	// Item
	Item* pItemA = new Item(m_Inventory[0][_iInvenIndex]);
	Item* pItemB = new Item(m_Storage[0][_iPage][_iStorageIndex]);

	// RemoveItem
	RemoveItemInInven(_iInvenIndex);
	RemoveItemInStorage(_iPage, _iStorageIndex);

	// Pos
	pItemA->iPosX = pItemB->iPosX;
	pItemA->iPosY = pItemB->iPosY;
	pItemB->iPosX = _iPosX;
	pItemB->iPosY = _iPosY;

	// AddItemA
	if(AddItemInStorage(_iPage, pItemA) == false)
	{
		delete pItemA;
		delete pItemB;
		return false;
	}

	// AddItemB
	if(AddItemInInven(pItemB) == false)
	{
		delete pItemB;
		return false;
	}

	return true;
}

bool CItemMgr::DevideStorageToInven(int _iPage, int _iStorageIndex, Item* _pItem)
{
	// Item
	Item* pItem = new Item(_pItem);

	// Num
	m_Storage[0][_iPage][_iStorageIndex]->iNum -= pItem->iNum;

	// AddItemInInven
	if(AddItemInInven(pItem))
		return true;

	delete pItem;
	return false;
}

bool CItemMgr::EnchantStorageToInven(int _iPage, int _iStorageIndex, int _iInvenIndex)
{
	// Check Sock
	if(m_Inventory[0][_iInvenIndex]->iSockNum == m_Inventory[0][_iInvenIndex]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Storage[0][_iPage][_iStorageIndex]);
	pGem->iNum = 1;
	m_Inventory[0][_iInvenIndex]->SockArr[m_Inventory[0][_iInvenIndex]->iSockCnt++] = pGem;

	if(m_Storage[0][_iPage][_iStorageIndex]->iNum == 1)
		RemoveItemInStorage(_iPage, _iInvenIndex);
	else
		m_Storage[0][_iPage][_iStorageIndex]->iNum -= 1;

	return true;
}

bool CItemMgr::MoveStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex)
{
	// TempItem
	Item* pTempItem = NULL;
	if(_iEquipIndex == 9 && m_pEquipment[0][11] != NULL)
	{
		// 왼쪽이 한손도끼일 때,
		if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 활일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_BOW)
		{
			// 왼쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 의식용칼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 왼쪽이 주먹무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_FIST)
		{
		}
		// 왼쪽이 손쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
		}
		// 왼쪽이 철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 오른쪽이 손쇠뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 화살통일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 왼쪽이 거대한손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
		}
		// 왼쪽이 거대두손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 방패일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
		}
		// 왼쪽이 창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 지팡이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_STAFF)
		{
			// 오른쪽이 방패, 오브, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손도끼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 완드일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 왼쪽이 액막이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MOJO)
		{
		}
		// 왼쪽이 쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 오브일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_ORB)
		{
		}
	}

	if(_iEquipIndex == 11 && m_pEquipment[0][9] != NULL)
	{
		// 오른쪽이 한손도끼일 때,
		if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 활일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_BOW)
		{
		}
		// 오른쪽이 의식용칼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 오른쪽이 주먹무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_FIST)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 손쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
			// 왼쪽이 손쇠뇌가 아니면 해제한다.
			if(false == (m_pEquipment[0][9]->dwItemID & WEAPON_ID_HANDXBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
		}
		// 오른쪽이 화살통일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 오른쪽이 거대한손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 거대두손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
		}
		// 오른쪽이 방패일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 지팡이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_STAFF)
		{
		}
		// 오른쪽이 검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손도끼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
		}
		// 오른쪽이 두손철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
		}
		// 오른쪽이 두손검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
		}
		// 오른쪽이 완드일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 오른쪽이 액막이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MOJO)
		{
			// 왼쪽이 양손창, 양손도끼, 양손철퇴, 양손검, 스태프, 활, 석궁이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_STAFF | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
		}
		// 오른쪽이 오브일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_ORB)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
	}

	// StorageItem
	Item* pStorageItem = new Item(m_Storage[0][_iPage][_iStorageIndex]);
	RemoveItemInStorage(_iPage, _iStorageIndex);

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pStorageItem) == false)
	{
		delete pStorageItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInInven
	if(pTempItem != NULL)
	{
		if(AddItemInInven(pTempItem) == false)
		{
			delete pTempItem;
			return false;
		}
	}

	// Sort
	if(m_pEquipment[0][9] == NULL && m_pEquipment[0][11] != NULL && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		m_pEquipment[0][9] = m_pEquipment[0][11];
		m_pEquipment[0][11] = NULL;
	}

	return true;
}

bool CItemMgr::MoveEquipToStorage(int _iEquipIndex, int _iPage, int _iPosX, int _iPosY)
{
	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	RemoveItemInEquip(_iEquipIndex);

	// AddItemInInven
	pEquipItem->iPosX = _iPosX;
	pEquipItem->iPosY = _iPosY;
	AddItemInStorage(_iPage, pEquipItem);

	return true;
}

bool CItemMgr::SwapStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex, int _iPosX /*= -1*/, int _iPosY /*= -1*/)
{
	// TempItem
	Item* pTempItem = NULL;
	if(_iEquipIndex == 9 && m_pEquipment[0][11] != NULL)
	{
		// 왼쪽이 한손도끼일 때,
		if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 활일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_BOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 의식용칼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 왼쪽이 주먹무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_FIST)
		{
		}
		// 왼쪽이 손쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
		}
		// 왼쪽이 철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 화살통일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 왼쪽이 거대한손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
		}
		// 왼쪽이 거대두손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 방패일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
		}
		// 왼쪽이 창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 지팡이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_STAFF)
		{
			// 오른쪽이 방패, 오브, 액막이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 오른쪽이 손소뇌이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & WEAPON_ID_HANDXBOW)
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손도끼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 두손검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			// 오른쪽이 방패, 오브, 도끼, 창, 철퇴, 검, 한손거대무기, 액막이이면 해제한다.
			if(m_pEquipment[0][11]->dwItemID & (WEAPON_ID_SHIELD | WEAPON_ID_ORB | WEAPON_ID_AXE | WEAPON_ID_SPEAR | WEAPON_ID_MACE | WEAPON_ID_MIGHTY1H | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H | WEAPON_ID_MOJO))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 완드일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 왼쪽이 액막이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MOJO)
		{
		}
		// 왼쪽이 쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
			// 오른쪽이 화살통이 아니면 해제한다.
			if(false == (m_pEquipment[0][11]->dwItemID & WEAPON_ID_QUIVER))
			{
				pTempItem = new Item(m_pEquipment[0][11]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(11);
			}
		}
		// 왼쪽이 오브일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_ORB)
		{
		}
	}

	if(_iEquipIndex == 11 && m_pEquipment[0][9] != NULL)
	{
		// 오른쪽이 한손도끼일 때,
		if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_AXE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 활일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_BOW)
		{
		}
		// 오른쪽이 의식용칼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
		}
		// 오른쪽이 주먹무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_FIST)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 손쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_HANDXBOW)
		{
			// 왼쪽이 손쇠뇌가 아니면 해제한다.
			if(false == (m_pEquipment[0][9]->dwItemID & WEAPON_ID_HANDXBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MACE)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_POLEARM)
		{
		}
		// 오른쪽이 화살통일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_QUIVER)
		{
		}
		// 오른쪽이 거대한손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY1H)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 거대두손무기일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MIGHTY2H)
		{
		}
		// 오른쪽이 방패일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SHIELD)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 창일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SPEAR)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 지팡이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_STAFF)
		{
		}
		// 오른쪽이 검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_SWORD)
		{
			// 왼쪽이 양손창, 양손거대무기, 양손도끼, 양손철퇴, 양손검이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 두손도끼일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
		}
		// 오른쪽이 두손철퇴일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_MACE)	
		{
		}
		// 오른쪽이 두손검일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
		}
		// 오른쪽이 완드일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_WAND)
		{
		}
		// 오른쪽이 액막이일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_MOJO)
		{
			// 왼쪽이 양손창, 양손도끼, 양손철퇴, 양손검, 스태프, 활, 석궁이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_STAFF | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
		// 오른쪽이 쇠뇌일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_CROSSBOW)
		{
		}
		// 오른쪽이 오브일 때,
		else if(m_Storage[0][_iPage][_iStorageIndex]->dwItemID & WEAPON_ID_ORB)
		{
			// 왼쪽이 쇠뇌, 활, 스태프, 두손도끼, 두손철퇴, 두손검, 두손창이면 해제한다.
			if(m_pEquipment[0][9]->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_POLEARM))
			{
				pTempItem = new Item(m_pEquipment[0][9]);
				pTempItem->iPosX = -1;
				pTempItem->iPosY = -1;
				RemoveItemInEquip(9);
			}
		}
	}

	// StorageItem
	Item* pStorageItem = new Item(m_Storage[0][_iPage][_iStorageIndex]);
	RemoveItemInStorage(_iPage, _iStorageIndex);

	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	pEquipItem->iPosX = (_iPosX == -1 ? pStorageItem->iPosX : _iPosX);
	pEquipItem->iPosY = (_iPosY == -1 ? pStorageItem->iPosY : _iPosY);
	RemoveItemInEquip(_iEquipIndex);

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pStorageItem) == false)
	{
		delete pStorageItem;
		delete pEquipItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInStorage
	if(AddItemInStorage(_iPage, pEquipItem) == false)
	{
		delete pEquipItem;
		if(pTempItem != NULL) { delete pTempItem; }
		return false;
	}

	// AddItemInInven
	if(pTempItem != NULL)
	{
		if(AddItemInInven(pTempItem) == false)
		{
			delete pTempItem;
			return false;
		}
	}

	// Sort
	if(m_pEquipment[0][9] == NULL && m_pEquipment[0][11] != NULL && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (m_pEquipment[0][11]->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		m_pEquipment[0][9] = m_pEquipment[0][11];
		m_pEquipment[0][11] = NULL;
	}

	return true;
}

bool CItemMgr::EnchantStorageToEquip(int _iPage, int _iStorageIndex, int _iEquipIndex)
{
	// Check Sock
	if(m_pEquipment[0][_iEquipIndex]->iSockNum == m_pEquipment[0][_iEquipIndex]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Storage[0][_iPage][_iStorageIndex]);
	pGem->iNum = 1;
	m_pEquipment[0][_iEquipIndex]->SockArr[m_pEquipment[0][_iEquipIndex]->iSockCnt++] = pGem;

	if(m_Storage[0][_iPage][_iStorageIndex]->iNum == 1)
		RemoveItemInStorage(_iPage, _iStorageIndex);
	else
		m_Storage[0][_iPage][_iStorageIndex]->iNum -= 1;

	return true;
}

void CItemMgr::CommitStorage(int _iPage)
{
	// Clear
	for(size_t i = 0; i < m_Storage[1][_iPage].size(); ++i)
		delete m_Storage[1][_iPage][i];
	m_Storage[1][_iPage].clear();

	// Copy
	for(size_t i = 0; i < m_Storage[0][_iPage].size(); ++i)
	{
		Item* pItem = new Item(m_Storage[0][_iPage][i]);
		m_Storage[1][_iPage].push_back(pItem);
	}
}

void CItemMgr::RollbackStorage(int _iPage)
{
	// Clear
	for(size_t i = 0; i < m_Storage[0][_iPage].size(); ++i)
		delete m_Storage[0][_iPage][i];
	m_Storage[0][_iPage].clear();

	// Copy
	for(size_t i = 0; i < m_Storage[1][_iPage].size(); ++i)
	{
		Item* pItem = new Item(m_Storage[1][_iPage][i]);
		m_Storage[0][_iPage].push_back(pItem);
	}
}

void CItemMgr::ResetStorage(int _iPage)
{
	for(size_t i = 0; i < m_Storage[0][_iPage].size(); ++i)
		delete m_Storage[0][_iPage][i];
	m_Storage[0][_iPage].clear();

	for(size_t i = 0; i < m_Storage[1][_iPage].size(); ++i)
		delete m_Storage[1][_iPage][i];
	m_Storage[1][_iPage].clear();
}

////////////////////////////////////////////////////////////////////////// FollowerEquipment
int CItemMgr::GetSizeOfFollowerEquip()
{
	int iCnt = 0;
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[0][i] != NULL)
			++iCnt;
	}

	return iCnt;
}

Item* CItemMgr::GetItemInFollowerEquip(int _iIndex)
{
	if(_iIndex >= 5)
		return NULL;

	return m_pFollowerEquipment[0][_iIndex];
}

bool CItemMgr::RemoveItemInFollowerEquip(int _iIndex)
{
	if(_iIndex >= 5)
		return false;

	if(m_pFollowerEquipment[0][_iIndex] == NULL)
		return false;

	delete m_pFollowerEquipment[0][_iIndex];
	m_pFollowerEquipment[0][_iIndex] = NULL;
	return true;
}

bool CItemMgr::SetItemInFollowerEquip(int _iIndex, Item* _pItem)
{
	if(_iIndex >= 5)
		return false;

	if(m_pFollowerEquipment[0][_iIndex] != NULL)
		return false;

	m_pFollowerEquipment[0][_iIndex] = _pItem;
	return true;
}

bool CItemMgr::MoveInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex)
{
	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pInvenItem) == false)
	{
		delete pInvenItem;
		return false;
	}

	return true;
}

bool CItemMgr::SwapInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex, int _iPosX /*= -1*/, int _iPosY /*= -1*/)
{
	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	pFollowerEquipItem->iPosX = (_iPosX == -1 ? pInvenItem->iPosX : _iPosX);
	pFollowerEquipItem->iPosY = (_iPosY == -1 ? pInvenItem->iPosY : _iPosY);
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pInvenItem) == false)
	{
		delete pInvenItem;
		delete pFollowerEquipItem;
		return false;
	}

	// AddItemInInven
	if(AddItemInInven(pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::MoveFollowerEquipToInven(int _iFollowerEquipIndex, int _iPosX, int _iPosY)
{
	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// AddItemInInven
	pFollowerEquipItem->iPosX = _iPosX;
	pFollowerEquipItem->iPosY = _iPosY;
	if(AddItemInInven(pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::SwapFollowerEquipToInven(int _iFollowerEquipIndex, int _iInvenIndex, int _iPosX, int _iPosY)
{
	// InvenItem
	Item* pInvenItem = new Item(m_Inventory[0][_iInvenIndex]);
	RemoveItemInInven(_iInvenIndex);

	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	pFollowerEquipItem->iPosX = _iPosX;
	pFollowerEquipItem->iPosY = _iPosY;
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pInvenItem) == false)
	{
		delete pInvenItem;
		delete pFollowerEquipItem;
		return false;
	}

	// AddItemInInven
	if(AddItemInInven(pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::MoveEquipToFollowerEquip(int _iEquipIndex, int _iFollowerEquipIndex)
{
	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	RemoveItemInEquip(_iEquipIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pEquipItem) == false)
	{
		delete pEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::SwapEquipToFollowerEquip(int _iEquipIndex, int _iFollowerEquipIndex)
{
	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	RemoveItemInEquip(_iEquipIndex);

	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pEquipItem) == false)
	{
		delete pEquipItem;
		delete pFollowerEquipItem;
		return false;
	}

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::MoveFollowerEquipToEquip(int _iFollowerEquipIndex, int _iEquipIndex)
{
	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::SwapFollowerEquipToEquip(int _iFollowerEquipIndex, int _iEquipIndex)
{
	// EquipItem
	Item* pEquipItem = new Item(m_pEquipment[0][_iEquipIndex]);
	RemoveItemInEquip(_iEquipIndex);

	// FollowerEquipItem
	Item* pFollowerEquipItem = new Item(m_pFollowerEquipment[0][_iFollowerEquipIndex]);
	RemoveItemInFollowerEquip(_iFollowerEquipIndex);

	// SetItemInFollowerEquip
	if(SetItemInFollowerEquip(_iFollowerEquipIndex, pEquipItem) == false)
	{
		delete pEquipItem;
		delete pFollowerEquipItem;
		return false;
	}

	// SetItemInEquip
	if(SetItemInEquip(_iEquipIndex, pFollowerEquipItem) == false)
	{
		delete pFollowerEquipItem;
		return false;
	}

	return true;
}

bool CItemMgr::EnchantInvenToFollowerEquip(int _iInvenIndex, int _iFollowerEquipIndex)
{
	// Check Sock
	if(m_pFollowerEquipment[0][_iFollowerEquipIndex]->iSockNum == m_pFollowerEquipment[0][_iFollowerEquipIndex]->iSockCnt)
		return false;

	// Enchant
	Item* pGem = new Item(m_Inventory[0][_iInvenIndex]);
	pGem->iNum = 1;
	m_pFollowerEquipment[0][_iFollowerEquipIndex]->SockArr[m_pFollowerEquipment[0][_iFollowerEquipIndex]->iSockCnt++] = pGem;

	if(m_Inventory[0][_iInvenIndex]->iNum == 1)
		RemoveItemInInven(_iInvenIndex);
	else
		m_Inventory[0][_iInvenIndex]->iNum -= 1;

	return true;
}

bool CItemMgr::SwapInFollowerEquip(int _iIndexA, int _iIndexB)
{
	Item* pTemp = m_pFollowerEquipment[0][_iIndexA];
	m_pFollowerEquipment[0][_iIndexA] = m_pFollowerEquipment[0][_iIndexB];
	m_pFollowerEquipment[0][_iIndexB] = pTemp;

	return true;
}

void CItemMgr::CommitFollowerEquip()
{
	// Clear
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[1][i] != NULL)
		{
			delete m_pFollowerEquipment[1][i];
			m_pFollowerEquipment[1][i] = NULL;
		}
	}

	// Copy
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[0][i] != NULL)
			m_pFollowerEquipment[1][i] = new Item(m_pFollowerEquipment[0][i]);
	}
}

void CItemMgr::RollbackFollowerEquip()
{
	// Clear
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[0][i] != NULL)
		{
			delete m_pFollowerEquipment[0][i];
			m_pFollowerEquipment[0][i] = NULL;
		}
	}

	// Copy
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[1][i] != NULL)
			m_pFollowerEquipment[0][i] = new Item(m_pFollowerEquipment[1][i]);
	}
}

void CItemMgr::ResetFollowerEquip()
{
	for(int i = 0; i < 5; ++i)
	{
		if(m_pFollowerEquipment[0][i] != NULL)
		{
			delete m_pFollowerEquipment[0][i];
			m_pFollowerEquipment[0][i] = NULL;
		}

		if(m_pFollowerEquipment[1][i] != NULL)
		{
			delete m_pFollowerEquipment[1][i];
			m_pFollowerEquipment[1][i] = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////// Item
Item* CItemMgr::CreateItem(DWORD _dwItemClass, DWORD _dwItemType, DWORD _dwItemID, int _iLevel)
{
	Item* pItem = new Item;
	pItem->dwItemClass = _dwItemClass;
	pItem->dwItemType = _dwItemType;
	pItem->iLevel = _iLevel;
	pItem->iGender = 2;

	// 한손무기
	if((_dwItemType & ITEM_TYPE_MAIN_WEAPON) && (_dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		// ID
		int iRand = rand() % 9;
		if(iRand == 0)
			pItem->dwItemID = WEAPON_ID_AXE;
		else if(iRand == 1)
			pItem->dwItemID = WEAPON_ID_CEREMONIAL_DAGGER;
		else if(iRand == 2)
			pItem->dwItemID = WEAPON_ID_FIST;
		else if(iRand == 3)
			pItem->dwItemID = WEAPON_ID_HANDXBOW;
		else if(iRand == 4)
			pItem->dwItemID = WEAPON_ID_MACE;
		else if(iRand == 5)
			pItem->dwItemID = WEAPON_ID_MIGHTY1H;
		else if(iRand == 6)
			pItem->dwItemID = WEAPON_ID_SPEAR;
		else if(iRand == 7)
			pItem->dwItemID = WEAPON_ID_SWORD;
		else if(iRand == 8)
			pItem->dwItemID = WEAPON_ID_WAND;

		// SockNum
		pItem->iSockNum = rand() % 3;
	}
	// 두손무기
	else if(_dwItemType & ITEM_TYPE_MAIN_WEAPON)
	{
		// ID
		int iRand = rand() % 8;
		if(iRand == 0)
			pItem->dwItemID = WEAPON_ID_BOW;
		else if(iRand == 1)
			pItem->dwItemID = WEAPON_ID_POLEARM;
		else if(iRand == 2)
			pItem->dwItemID = WEAPON_ID_MIGHTY2H;
		else if(iRand == 3)
			pItem->dwItemID = WEAPON_ID_STAFF;
		else if(iRand == 4)
			pItem->dwItemID = WEAPON_ID_TWO_HAND_AXE;
		else if(iRand == 5)
			pItem->dwItemID = WEAPON_ID_TWO_HAND_MACE;
		else if(iRand == 6)
			pItem->dwItemID = WEAPON_ID_TWO_HAND_SWORD;
		else if(iRand == 7)
			pItem->dwItemID = WEAPON_ID_CROSSBOW;

		// SockNyum
		pItem->iSockNum = rand() % 3;
	}
	// 보조무기
	else if(_dwItemType & ITEM_TYPE_SUB_WEAPON)
	{
		// ID
		int iRand = rand() % 4;
		if(iRand == 0)
			pItem->dwItemID = WEAPON_ID_QUIVER;
		else if(iRand == 1)
			pItem->dwItemID = WEAPON_ID_SHIELD;
		else if(iRand == 2)
			pItem->dwItemID = WEAPON_ID_MOJO;
		else if(iRand == 3)
			pItem->dwItemID = WEAPON_ID_ORB;

		// SockNum
		pItem->iSockNum = rand() % 3;
	}
	else if(_dwItemType & ITEM_TYPE_HELMS)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = HELMS_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = HELMS_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = HELMS_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = HELMS_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = HELMS_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;
	}
	else if(_dwItemType & ITEM_TYPE_SHOULDERS)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = SHOULDERS_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = SHOULDERS_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = SHOULDERS_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = SHOULDERS_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = SHOULDERS_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;
	}
	else if(_dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = CHESTARMOR_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = CHESTARMOR_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = CHESTARMOR_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = CHESTARMOR_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = CHESTARMOR_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 4;
	}
	else if(_dwItemType & ITEM_TYPE_BRACERS)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = BRACERS_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = BRACERS_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = BRACERS_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = BRACERS_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = BRACERS_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;

	}
	else if(_dwItemType & ITEM_TYPE_GLOVES)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = GLOVES_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = GLOVES_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = GLOVES_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = GLOVES_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = GLOVES_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;
	}
	else if(_dwItemType & ITEM_TYPE_BELT)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = BELT_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = BELT_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = BELT_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = BELT_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = BELT_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;
	}
	else if(_dwItemType & ITEM_TYPE_PANTS)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = PANTS_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = PANTS_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = PANTS_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = PANTS_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = PANTS_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 3;
	}
	else if(_dwItemType & ITEM_TYPE_BOOTS)
	{
		// ID
		int iRand = rand() % 5;
		if(iRand == 0)
			pItem->dwItemID = BOOTS_ID_BARBARIAN;
		else if(iRand == 1)
			pItem->dwItemID = BOOTS_ID_DEMONHUNTER;
		else if(iRand == 2)
			pItem->dwItemID = BOOTS_ID_MONK;
		else if(iRand == 3)
			pItem->dwItemID = BOOTS_ID_WITCHDOCTOR;
		else if(iRand == 4)
			pItem->dwItemID = BOOTS_ID_WIZARD;

		// SockNum
		pItem->iSockNum = rand() % 2;
	}
	else if(_dwItemType & ITEM_TYPE_AMULET)
	{
		pItem->dwItemID = AMULET_ID_AMULET;
	}
	else if(_dwItemType & ITEM_TYPE_RING)
	{
		pItem->dwItemID = RING_ID_RING;
	}
	// 보석
	else if(_dwItemType & ITEM_TYPE_GEM)
	{
		pItem->dwItemClass = 0;
		pItem->iLevel = 0;
		pItem->iGender = 2;

		int iRand = rand() % 30;
		if(iRand == 0)
			pItem->dwItemID = GEM_ID_TOPAZ1;
		else if(iRand == 1)
			pItem->dwItemID = GEM_ID_TOPAZ2;
		else if(iRand == 2)
			pItem->dwItemID = GEM_ID_TOPAZ3;
		else if(iRand == 3)
			pItem->dwItemID = GEM_ID_TOPAZ4;
		else if(iRand == 4)
			pItem->dwItemID = GEM_ID_TOPAZ5;
		else if(iRand == 5)
			pItem->dwItemID = GEM_ID_SAPPHIRE1;
		else if(iRand == 6)
			pItem->dwItemID = GEM_ID_SAPPHIRE2;
		else if(iRand == 7)
			pItem->dwItemID = GEM_ID_SAPPHIRE3;
		else if(iRand == 8)
			pItem->dwItemID = GEM_ID_SAPPHIRE4;
		else if(iRand == 9)
			pItem->dwItemID = GEM_ID_SAPPHIRE5;
		else if(iRand == 10)
			pItem->dwItemID = GEM_ID_RUBY1;
		else if(iRand == 11)
			pItem->dwItemID = GEM_ID_RUBY2;
		else if(iRand == 12)
			pItem->dwItemID = GEM_ID_RUBY3;
		else if(iRand == 13)
			pItem->dwItemID = GEM_ID_RUBY4;
		else if(iRand == 14)
			pItem->dwItemID = GEM_ID_RUBY5;
		else if(iRand == 15)
			pItem->dwItemID = GEM_ID_EMERALD1;
		else if(iRand == 16)
			pItem->dwItemID = GEM_ID_EMERALD2;
		else if(iRand == 17)
			pItem->dwItemID = GEM_ID_EMERALD3;
		else if(iRand == 18)
			pItem->dwItemID = GEM_ID_EMERALD4;
		else if(iRand == 19)
			pItem->dwItemID = GEM_ID_EMERALD5;
		else if(iRand == 20)
			pItem->dwItemID = GEM_ID_DIAMOND1;
		else if(iRand == 21)
			pItem->dwItemID = GEM_ID_DIAMOND2;
		else if(iRand == 22)
			pItem->dwItemID = GEM_ID_DIAMOND3;
		else if(iRand == 23)
			pItem->dwItemID = GEM_ID_DIAMOND4;
		else if(iRand == 24)
			pItem->dwItemID = GEM_ID_DIAMOND5;
		else if(iRand == 25)
			pItem->dwItemID = GEM_ID_AMETHYST1;
		else if(iRand == 26)
			pItem->dwItemID = GEM_ID_AMETHYST2;
		else if(iRand == 27)
			pItem->dwItemID = GEM_ID_AMETHYST3;
		else if(iRand == 28)
			pItem->dwItemID = GEM_ID_AMETHYST4;
		else if(iRand == 29)
			pItem->dwItemID = GEM_ID_AMETHYST5;
	}
	// 재료
	else if(_dwItemType & ITEM_TYPE_MATERIAL)
	{
		pItem->dwItemClass = 0;
		pItem->iLevel = 0;
		pItem->iGender = 2;

		int iRand = rand() % 7;
		if(iRand == 0)
			pItem->dwItemID = MATERIAL_ID_IRON;
		else if(iRand == 1)
			pItem->dwItemID = MATERIAL_ID_CRYSTAL;
		else if(iRand == 2)
			pItem->dwItemID = MATERIAL_ID_PATTERNS;
		else if(iRand == 3)
			pItem->dwItemID = MATERIAL_ID_DIAMOND;
		else if(iRand == 4)
			pItem->dwItemID = MATERIAL_ID_MANA_SOURCE;
		else if(iRand == 5)
			pItem->dwItemID = MATERIAL_ID_ADAMANTIUM;
		else if(iRand == 6)
			pItem->dwItemID = MATERIAL_ID_METAL_STAIN;
	}

	if(_dwItemID != 0)
		pItem->dwItemID = _dwItemID;

	CreateName(pItem);
	CreateTexKey(pItem);
	CreateBufKey(pItem);
	CreateSize(pItem);
	CreateStat(pItem);
	CreateValue(pItem);

	if(pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		pItem->iAtt = int(pItem->iAtt * 1.1f);
		pItem->iDef = int(pItem->iDef * 1.1f);
		pItem->iValue = int(pItem->iValue * 1.1f);
	}
	else if(pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		pItem->iAtt = int(pItem->iAtt * 1.2f);
		pItem->iDef = int(pItem->iDef * 1.2f);
		pItem->iValue = int(pItem->iValue * 1.2f);
	}
	else if(pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		pItem->iAtt = int(pItem->iAtt * 1.3f);
		pItem->iDef = int(pItem->iDef * 1.3f);
		pItem->iValue = int(pItem->iValue * 1.3f);
	}
	else if(pItem->dwItemClass & ITEM_CLASS_SET)
	{
		pItem->iAtt = int(pItem->iAtt * 1.4f);
		pItem->iDef = int(pItem->iDef * 1.4f);
		pItem->iValue = int(pItem->iValue * 1.4f);
	}

 	return pItem;
}

void CItemMgr::CreateName(Item* _pItem)
{
	ZeroMemory(_pItem->tszName, sizeof(_pItem->tszName));

	// 형용사
	if(_pItem->dwItemClass & ITEM_CLASS_NORMAL)
	{
		int iRand = rand() % 3;
		if(iRand == 0)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("일반 "));
		else if(iRand == 1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("희미한 "));
		else if(iRand == 2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("3세대 "));
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		int iRand = rand() % 3;
		if(iRand == 0)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("매직 "));
		else if(iRand == 1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("은은한 "));
		else if(iRand == 2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("4세대 "));
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		int iRand = rand() % 3;
		if(iRand == 0)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("희귀 "));
		else if(iRand == 1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("빛나는 "));
		else if(iRand == 2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("5세대 "));
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		int iRand = rand() % 3;
		if(iRand == 0)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("전설 "));
		else if(iRand == 1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("화려한 "));
		else if(iRand == 2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("6세대 "));
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_SET)
	{
		int iRand = rand() % 3;
		if(iRand == 0)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("세트 "));
		else if(iRand == 1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("찬란한 "));
		else if(iRand == 2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("7세대 "));
	}

	// 목걸이
	if(_pItem->dwItemType & ITEM_TYPE_AMULET)
	{
		if(_pItem->dwItemID & AMULET_ID_AMULET)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("목걸이"));
	}
	// 반지
	else if(_pItem->dwItemType & ITEM_TYPE_RING)
	{
		if(_pItem->dwItemID & RING_ID_RING)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("반지"));
	}
	// 보석
	else if(_pItem->dwItemType & ITEM_TYPE_GEM)
	{
		if(_pItem->dwItemID & GEM_ID_TOPAZ1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 토파즈"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 토파즈"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 토파즈"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 토파즈"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 토파즈"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 사파이어"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 사파이어"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 사파이어"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 사파이어"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 사파이어"));
		else if(_pItem->dwItemID & GEM_ID_RUBY1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 루비"));
		else if(_pItem->dwItemID & GEM_ID_RUBY2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 루비"));
		else if(_pItem->dwItemID & GEM_ID_RUBY3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 루비"));
		else if(_pItem->dwItemID & GEM_ID_RUBY4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 루비"));
		else if(_pItem->dwItemID & GEM_ID_RUBY5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 루비"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 에메랄드"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 에메랄드"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 에메랄드"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 에메랄드"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 에메랄드"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 다이아몬드"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 다이아몬드"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 다이아몬드"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 다이아몬드"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 다이아몬드"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST1)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨1 자수정"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST2)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨2 자수정"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST3)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨3 자수정"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST4)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨4 자수정"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST5)
			_tcscpy_s(_pItem->tszName, MIN_STR, _T("레벨5 자수정"));
	}
	// 재료
	else if(_pItem->dwItemType & ITEM_TYPE_MATERIAL)
	{
		if(_pItem->dwItemID & MATERIAL_ID_IRON)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("쇠조각"));
		else if(_pItem->dwItemID & MATERIAL_ID_CRYSTAL)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수정"));
		else if(_pItem->dwItemID & MATERIAL_ID_PATTERNS)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("문양"));
		else if(_pItem->dwItemID & MATERIAL_ID_DIAMOND)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("다이아몬드"));
		else if(_pItem->dwItemID & MATERIAL_ID_MANA_SOURCE)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마력원"));
		else if(_pItem->dwItemID & MATERIAL_ID_ADAMANTIUM)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("아다만티움"));
		else if(_pItem->dwItemID & MATERIAL_ID_METAL_STAIN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("쇳물"));
	}
	// 신발
	else if(_pItem->dwItemType & ITEM_TYPE_BOOTS)
	{
		if(_pItem->dwItemID & BOOTS_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 신발"));
		else if(_pItem->dwItemID & BOOTS_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 신발"));
		else if(_pItem->dwItemID & BOOTS_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 신발"));
		else if(_pItem->dwItemID & BOOTS_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 신발"));
		else if(_pItem->dwItemID & BOOTS_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 신발"));
	}
	// 장갑
	else if(_pItem->dwItemType & ITEM_TYPE_GLOVES)
	{
		if(_pItem->dwItemID & GLOVES_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 장갑"));
		else if(_pItem->dwItemID & GLOVES_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 장갑"));
		else if(_pItem->dwItemID & GLOVES_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 장갑"));
		else if(_pItem->dwItemID & GLOVES_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 장갑"));
		else if(_pItem->dwItemID & GLOVES_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 장갑"));
	}
	// 모자
	else if(_pItem->dwItemType & ITEM_TYPE_HELMS)
	{
		if(_pItem->dwItemID & HELMS_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 모자"));
		else if(_pItem->dwItemID & HELMS_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 모자"));
		else if(_pItem->dwItemID & HELMS_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 모자"));
		else if(_pItem->dwItemID & HELMS_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 모자"));
		else if(_pItem->dwItemID & HELMS_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 모자"));
	}
	// 바지
	else if(_pItem->dwItemType & ITEM_TYPE_PANTS)
	{
		if(_pItem->dwItemID & PANTS_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 바지"));
		else if(_pItem->dwItemID & PANTS_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 바지"));
		else if(_pItem->dwItemID & PANTS_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 바지"));
		else if(_pItem->dwItemID & PANTS_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 바지"));
		else if(_pItem->dwItemID & PANTS_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 바지"));
	}
	// 어깨보호대
	else if(_pItem->dwItemType & ITEM_TYPE_SHOULDERS)
	{
		if(_pItem->dwItemID & SHOULDERS_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 어깨보호대"));
		else if(_pItem->dwItemID & SHOULDERS_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 어깨보호대"));
		else if(_pItem->dwItemID & SHOULDERS_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 어깨보호대"));
		else if(_pItem->dwItemID & SHOULDERS_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 어깨보호대"));
		else if(_pItem->dwItemID & SHOULDERS_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 어깨보호대"));
	}
	// 벨트
	else if(_pItem->dwItemType & ITEM_TYPE_BELT)
	{
		if(_pItem->dwItemID & BELT_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 벨트"));
		else if(_pItem->dwItemID & BELT_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 벨트"));
		else if(_pItem->dwItemID & BELT_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 벨트"));
		else if(_pItem->dwItemID & BELT_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 벨트"));
		else if(_pItem->dwItemID & BELT_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 벨트"));
	}
	// 손목보호대
	else if(_pItem->dwItemType & ITEM_TYPE_BRACERS)
	{
		if(_pItem->dwItemID & BRACERS_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 손목보호대"));
		else if(_pItem->dwItemID & BRACERS_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 손목보호대"));
		else if(_pItem->dwItemID & BRACERS_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 손목보호대"));
		else if(_pItem->dwItemID & BRACERS_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 손목보호대"));
		else if(_pItem->dwItemID & BRACERS_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 손목보호대"));
	}
	// 흉갑
	else if(_pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		if(_pItem->dwItemID & CHESTARMOR_ID_BARBARIAN)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("야만용사 흉갑"));
		else if(_pItem->dwItemID & CHESTARMOR_ID_DEMONHUNTER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("악마사냥꾼 흉갑"));
		else if(_pItem->dwItemID & CHESTARMOR_ID_MONK)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("수도사 흉갑"));
		else if(_pItem->dwItemID & CHESTARMOR_ID_WITCHDOCTOR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("부두술사 흉갑"));
		else if(_pItem->dwItemID & CHESTARMOR_ID_WIZARD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("마법사 흉갑"));
	}
	// 무기
	else if(_pItem->dwItemType & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON))
	{
		if(_pItem->dwItemID & WEAPON_ID_AXE)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("도끼"));
		else if(_pItem->dwItemID & WEAPON_ID_BOW)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("활"));
		else if(_pItem->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("의식용칼"));
		else if(_pItem->dwItemID & WEAPON_ID_FIST)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("너클"));
		else if(_pItem->dwItemID & WEAPON_ID_HANDXBOW)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("손쇠뇌"));
		else if(_pItem->dwItemID & WEAPON_ID_MACE)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("철퇴"));
		else if(_pItem->dwItemID & WEAPON_ID_POLEARM)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("폴암"));
		else if(_pItem->dwItemID & WEAPON_ID_QUIVER)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("화살통"));
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY1H)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("한손거대무기"));
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY2H)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("두손거대무기"));
		else if(_pItem->dwItemID & WEAPON_ID_SHIELD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("방패"));
		else if(_pItem->dwItemID & WEAPON_ID_SPEAR)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("창"));
		else if(_pItem->dwItemID & WEAPON_ID_STAFF)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("지팡이"));
		else if(_pItem->dwItemID & WEAPON_ID_SWORD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("검"));
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_AXE)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("양손도끼"));
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_MACE)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("양손철퇴"));
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("양손검"));
		else if(_pItem->dwItemID & WEAPON_ID_WAND)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("완드"));
		else if(_pItem->dwItemID & WEAPON_ID_MOJO)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("액막이"));
		else if(_pItem->dwItemID & WEAPON_ID_CROSSBOW)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("석궁"));
		else if(_pItem->dwItemID & WEAPON_ID_ORB)
			_tcscat_s(_pItem->tszName, MIN_STR, _T("오브"));
	}
}

void CItemMgr::CreateTexKey(Item* _pItem)
{
	ZeroMemory(_pItem->tszTexKey, sizeof(_pItem->tszTexKey));

	// 목걸이
	if(_pItem->dwItemType & ITEM_TYPE_AMULET)
	{
		if(_pItem->dwItemID & AMULET_ID_AMULET)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Amulet_"), rand() % 33 + 1);
	}
	// 반지
	else if(_pItem->dwItemType & ITEM_TYPE_RING)
	{
		if(_pItem->dwItemID & RING_ID_RING)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Rings_"), rand() % 42 + 1);
	}
	// 보석
	else if(_pItem->dwItemType & ITEM_TYPE_GEM)
	{
		if(_pItem->dwItemID & GEM_ID_TOPAZ1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_1"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_2"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_3"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_4"));
		else if(_pItem->dwItemID & GEM_ID_TOPAZ5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_5"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_6"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_7"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_8"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_9"));
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_10"));
		else if(_pItem->dwItemID & GEM_ID_RUBY1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_11"));
		else if(_pItem->dwItemID & GEM_ID_RUBY2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_12"));
		else if(_pItem->dwItemID & GEM_ID_RUBY3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_13"));
		else if(_pItem->dwItemID & GEM_ID_RUBY4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_14"));
		else if(_pItem->dwItemID & GEM_ID_RUBY5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_15"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_16"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_17"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_18"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_19"));
		else if(_pItem->dwItemID & GEM_ID_EMERALD5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_20"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_21"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_22"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_23"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_24"));
		else if(_pItem->dwItemID & GEM_ID_DIAMOND5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_25"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST1)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_26"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST2)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_27"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST3)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_28"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST4)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_29"));
		else if(_pItem->dwItemID & GEM_ID_AMETHYST5)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Gems_30"));
	}
	// 재료
	else if(_pItem->dwItemType & ITEM_TYPE_MATERIAL)
	{
		if(_pItem->dwItemID & MATERIAL_ID_IRON)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_1"));
		else if(_pItem->dwItemID & MATERIAL_ID_CRYSTAL)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_2"));
		else if(_pItem->dwItemID & MATERIAL_ID_PATTERNS)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_3"));
		else if(_pItem->dwItemID & MATERIAL_ID_DIAMOND)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_4"));
		else if(_pItem->dwItemID & MATERIAL_ID_MANA_SOURCE)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_5"));
		else if(_pItem->dwItemID & MATERIAL_ID_ADAMANTIUM)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_6"));
		else if(_pItem->dwItemID & MATERIAL_ID_METAL_STAIN)
			_tcscpy_s(_pItem->tszTexKey, MIN_STR, _T("Item_Materials_7"));
	}
	// 신발
	else if(_pItem->dwItemType & ITEM_TYPE_BOOTS)
	{
		if(_pItem->dwItemID & BOOTS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_BarbarianBoots_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & BOOTS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterBoots_"), rand() % 19 + 1);
		else if(_pItem->dwItemID & BOOTS_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkBoots_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & BOOTS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorBoots_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & BOOTS_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardBoots_"), rand() % 17 + 1);
	}
	// 장갑
	else if(_pItem->dwItemType & ITEM_TYPE_GLOVES)
	{
		if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_UniqueGloves_"), rand() % 20 + 1);
		else if(_pItem->dwItemID & GLOVES_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_BarbarianGloves_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & GLOVES_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterGloves_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & GLOVES_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkGloves_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & GLOVES_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorGloves_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & GLOVES_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardGloves_"), rand() % 17 + 1);
	}
	// 모자
	else if(_pItem->dwItemType & ITEM_TYPE_HELMS)
	{
		if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_UniqueHelms_"), rand() % 10 + 1);
		else if(_pItem->dwItemID & HELMS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_BarbarianHelms_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & HELMS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterHelms_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & HELMS_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkHelms_"), rand() % 34 + 1);
		else if(_pItem->dwItemID & HELMS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorHelms_"), rand() % 26 + 1);
		else if(_pItem->dwItemID & HELMS_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardHelms_"), rand() % 17 + 1);
	}
	// 바지
	else if(_pItem->dwItemType & ITEM_TYPE_PANTS)
	{
		if(_pItem->dwItemID & PANTS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_BarbarianPants_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & PANTS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterPants_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & PANTS_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkPants_"), rand() % 25 + 1);
		else if(_pItem->dwItemID & PANTS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorPants_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & PANTS_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardPants_"), rand() % 17 + 1);
	}
	// 어깨보호대
	else if(_pItem->dwItemType & ITEM_TYPE_SHOULDERS)
	{
		if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_UniqueShoulders_"), rand() % 7 + 1);
		else if(_pItem->dwItemID & SHOULDERS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_BarbarianShoulders_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & SHOULDERS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterShoulders_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & SHOULDERS_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkShoulders_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & SHOULDERS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorShoulders_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & SHOULDERS_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardShoulders_"), rand() % 17 + 1);
	}
	// 벨트
	else if(_pItem->dwItemType & ITEM_TYPE_BELT)
	{
		if(_pItem->dwItemID & BELT_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Belts_"), rand() % 30 + 1);
		else if(_pItem->dwItemID & BELT_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Belts_"), rand() % 30 + 1);
		else if(_pItem->dwItemID & BELT_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkBelts_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & BELT_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorBelts_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & BELT_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardBelts_"), rand() % 17 + 1);
	}
	// 손목보호대
	else if(_pItem->dwItemType & ITEM_TYPE_BRACERS)
	{
		if(_pItem->dwItemID & BRACERS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bracers_"), rand() % 27 + 1);
		else if(_pItem->dwItemID & BRACERS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bracers_"), rand() % 27 + 1);
		else if(_pItem->dwItemID & BRACERS_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bracers_"), rand() % 27 + 1);
		else if(_pItem->dwItemID & BRACERS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bracers_"), rand() % 27 + 1);
		else if(_pItem->dwItemID & BRACERS_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bracers_"), rand() % 27 + 1);
	}
	// 흉갑
	else if(_pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_UniqueChestArmor_"), rand() % 15 + 1);
		else if(_pItem->dwItemID & CHESTARMOR_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_ChestArmor_"), rand() % 8 + 1);
		else if(_pItem->dwItemID & CHESTARMOR_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_DemonHunterChestArmor_"), rand() % 42 + 1);
		else if(_pItem->dwItemID & CHESTARMOR_ID_MONK)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MonkChestArmor_"), rand() % 34 + 1);
		else if(_pItem->dwItemID & CHESTARMOR_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WitchDoctorChestArmor_"), rand() % 31 + 1);
		else if(_pItem->dwItemID & CHESTARMOR_ID_WIZARD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_WizardChestArmor_"), rand() % 31 + 1);
	}
	// 무기
	else if(_pItem->dwItemType & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON))
	{
		if(_pItem->dwItemID & WEAPON_ID_AXE)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Axes_"), rand() % 14 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_BOW)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Bows_"), rand() % 14 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_CeremonialDaggers_"), rand() % 12 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_FIST)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_FistWeapons_"), rand() % 18 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_HANDXBOW)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_HandXBows_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_MACE)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Maces_"), rand() % 18 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_POLEARM)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Polearms_"), rand() % 12 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_QUIVER)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Quivers_"), rand() % 15 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY1H)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MightyWeapon1H_"), rand() % 13 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY2H)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_MightyWeapon2H_"), rand() % 10 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_SHIELD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Shields_"), rand() % 16 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_SPEAR)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Spears_"), rand() % 9 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_STAFF)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Staves_"), rand() % 14 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_SWORD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Swords_"), rand() % 20 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_AXE)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_TwoHandedAxes_"), rand() % 12 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_MACE)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_TwoHandedMaces_"), rand() % 12 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_TwoHandedSwords_"), rand() % 17 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_WAND)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Wands_"), rand() % 15 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_MOJO)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Mojo_"), rand() % 12 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_CROSSBOW)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Crossbows_"), rand() % 15 + 1);
		else if(_pItem->dwItemID & WEAPON_ID_ORB)
			StringCbPrintf(_pItem->tszTexKey, sizeof(_pItem->tszTexKey), _T("%s%d"), _T("Item_Orbs_"), rand() % 5 + 1);
	}
}

void CItemMgr::CreateBufKey(Item* _pItem)
{
	ZeroMemory(_pItem->tszBufKey, sizeof(_pItem->tszBufKey));

	// 신발
	if(_pItem->dwItemType & ITEM_TYPE_BOOTS)
	{
		if(_pItem->dwItemID & BOOTS_ID_BARBARIAN)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_MED_Boots"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
		}
		else if(_pItem->dwItemID & BOOTS_ID_DEMONHUNTER)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
		}
		else if(_pItem->dwItemID & BOOTS_ID_MONK)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_MED_Boots"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
		}
		else if(_pItem->dwItemID & BOOTS_ID_WITCHDOCTOR)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_MED_Boots"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
		}
		else if(_pItem->dwItemID & BOOTS_ID_WIZARD)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Boots"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Boots"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Boots"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Boots"));
			}
		}
	}
	// 장갑
	else if(_pItem->dwItemType & ITEM_TYPE_GLOVES)
	{
		if(_pItem->dwItemID & GLOVES_ID_BARBARIAN)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_MED_Hands"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
		}
		else if(_pItem->dwItemID & GLOVES_ID_DEMONHUNTER)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
		}
		else if(_pItem->dwItemID & GLOVES_ID_MONK)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_MED_Hands"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
		}
		else if(_pItem->dwItemID & GLOVES_ID_WITCHDOCTOR)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_MED_Hands"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
		}
		else if(_pItem->dwItemID & GLOVES_ID_WIZARD)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Hands"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Hands"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Hands"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Hands"));
			}
		}
	}
	// 모자
	else if(_pItem->dwItemType & ITEM_TYPE_HELMS)
	{
		if(_pItem->dwItemID & HELMS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_BarbarianHelms_"), rand() % 32);
		else if(_pItem->dwItemID & HELMS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_DemonHunterHelms_"), rand() % 32);
		else if(_pItem->dwItemID & HELMS_ID_MONK)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_MonkHelms_"), rand() % 32);
		else if(_pItem->dwItemID & HELMS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_WitchDoctorHelms_"), rand() % 32);
		else if(_pItem->dwItemID & HELMS_ID_WIZARD)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_WizardHelms_"), rand() % 32);
	}
	// 바지
	else if(_pItem->dwItemType & ITEM_TYPE_PANTS)
	{
		if(_pItem->dwItemID & PANTS_ID_BARBARIAN)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_MED_Pants"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Pants"));
			}
		}
		else if(_pItem->dwItemID & PANTS_ID_DEMONHUNTER)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Pants"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Pants"));
			}
		}
		else if(_pItem->dwItemID & PANTS_ID_MONK)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_MED_Pants"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Pants"));
			}
		}
		else if(_pItem->dwItemID & PANTS_ID_WITCHDOCTOR)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_MED_Pants"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Pants"));
			}
		}
		else if(_pItem->dwItemID & PANTS_ID_WIZARD)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Pants"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Pants"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Pants"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Pants"));
			}
		}
	}
	// 어깨보호대
	else if(_pItem->dwItemType & ITEM_TYPE_SHOULDERS)
	{
		if(_pItem->dwItemID & SHOULDERS_ID_BARBARIAN)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_BarbarianShoulders_"), rand() % 32);
		else if(_pItem->dwItemID & SHOULDERS_ID_DEMONHUNTER)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_DemonHunterShoulders_"), rand() % 32);
		else if(_pItem->dwItemID & SHOULDERS_ID_MONK)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_MonkShoulders_"), rand() % 32);
		else if(_pItem->dwItemID & SHOULDERS_ID_WITCHDOCTOR)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_WitchDoctorShoulders_"), rand() % 32);
		else if(_pItem->dwItemID & SHOULDERS_ID_WIZARD)
			StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_WizardShoulders_"), rand() % 32);
	}
	// 흉갑
	else if(_pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		if(_pItem->dwItemID & CHESTARMOR_ID_BARBARIAN)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Barbarian_Male_MED_Upper"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 7;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_A"));
				else if(iRand == 3)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_B"));
				else if(iRand == 4)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Upper"));
				else if(iRand == 5)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Upper"));
				else if(iRand == 6)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Upper"));
			}
		}
		else if(_pItem->dwItemID & CHESTARMOR_ID_DEMONHUNTER)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 7;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_A"));
				else if(iRand == 3)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_B"));
				else if(iRand == 4)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Upper"));
				else if(iRand == 5)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Upper"));
				else if(iRand == 6)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Upper"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 7;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_A"));
				else if(iRand == 3)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_B"));
				else if(iRand == 4)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Upper"));
				else if(iRand == 5)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Upper"));
				else if(iRand == 6)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Upper"));
			}
		}
		else if(_pItem->dwItemID & CHESTARMOR_ID_MONK)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Monk_Male_MED_Upper"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 7;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_A"));
				else if(iRand == 3)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_B"));
				else if(iRand == 4)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Upper"));
				else if(iRand == 5)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Upper"));
				else if(iRand == 6)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Upper"));
			}
		}
		else if(_pItem->dwItemID & CHESTARMOR_ID_WITCHDOCTOR)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("WitchDoctor_Male_MED_Upper"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 7;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_A"));
				else if(iRand == 3)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_CLS_MED_Upper_B"));
				else if(iRand == 4)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_HVY_Upper"));
				else if(iRand == 5)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_LIT_Upper"));
				else if(iRand == 6)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("DemonHunter_Female_MED_Upper"));
			}
		}
		else if(_pItem->dwItemID & CHESTARMOR_ID_WIZARD)
		{
			_pItem->iGender = rand() % 2;
			if(_pItem->iGender == 0)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Upper"));
			}
			else if(_pItem->iGender == 1)
			{
				int iRand = rand() % 3;
				if(iRand == 0)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_HVY_Upper"));
				else if(iRand == 1)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_LIT_Upper"));
				else if(iRand == 2)
					_tcscpy_s(_pItem->tszBufKey, MIN_STR, _T("Wizard_Female_MED_Upper"));
			}
		}
	}
	// 무기
	else if(_pItem->dwItemType & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON))
	{
		if(_pItem->dwItemID & WEAPON_ID_AXE)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Axe_Unique"), rand() % 5);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Axe_Base"), rand() % 6);
		}
		else if(_pItem->dwItemID & WEAPON_ID_BOW)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Bow_Unique"), rand() % 7);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Bow_Base"), rand() % 6);
		}
		else if(_pItem->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_CeremonialDagger_Unique"), rand() % 5);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_CeremonialDagger_Base"), rand() % 4);
		}
		else if(_pItem->dwItemID & WEAPON_ID_FIST)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Fist_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Fist_Unique"), rand() % 9);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Fist_Base"), rand() % 4);
		}
		else if(_pItem->dwItemID & WEAPON_ID_HANDXBOW)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_HandXBow_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_HandXBow_Unique"), rand() % 6);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_HandXBow_Base"), rand() % 8);
		}
		else if(_pItem->dwItemID & WEAPON_ID_MACE)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mace_Unique"), rand() % 8);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mace_Base"), rand() % 7);
		}
		else if(_pItem->dwItemID & WEAPON_ID_POLEARM)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Polearm_Unique"), rand() % 3);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Polearm_Base"), rand() % 8);
		}
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY1H)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mighty1H_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mighty1H_Unique"), rand() % 5);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mighty1H_Base"), rand() % 4);
		}
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mighty2H_Unique"), rand() % 4);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mighty2H_Base"), rand() % 4);
		}
		else if(_pItem->dwItemID & WEAPON_ID_SHIELD)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Shield_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Shield_Unique"), rand() % 5);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Shield_Base"), rand() % 7);
		}
		else if(_pItem->dwItemID & WEAPON_ID_SPEAR)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Spear_Unique"), rand() % 3);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Spear_Base"), rand() % 5);
		}
		else if(_pItem->dwItemID & WEAPON_ID_STAFF)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Staff_Unique"), rand() % 4);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Staff_Base"), rand() % 7);
		}
		else if(_pItem->dwItemID & WEAPON_ID_SWORD)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Sword_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Sword_Unique"), rand() % 10);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Sword_Base"), rand() % 8);
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Axe_Unique"), rand() % 5);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Axe_Base"), rand() % 5);
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_MACE)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Mace_Unique"), rand() % 7);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Mace_Base"), rand() % 6);
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Sword_Unique"), rand() % 8);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Two_Handed_Sword_Base"), rand() % 6);
		}
		else if(_pItem->dwItemID & WEAPON_ID_MOJO)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mojo_Unique"), rand() % 6);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Mojo_Base"), rand() % 2);
		}
		else if(_pItem->dwItemID & WEAPON_ID_WAND)
		{
			if(_pItem->dwItemClass & ITEM_CLASS_SET)
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Wand_Set"), rand() % 1);
			else if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Wand_Unique"), rand() % 2);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Wand_Base"), rand() % 7);
		}
		else if(_pItem->dwItemID & WEAPON_ID_CROSSBOW)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_CrossBow_Unique"), rand() % 7);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_CrossBow_Base"), rand() % 8);
		}
		else if(_pItem->dwItemID & WEAPON_ID_ORB)
		{
			if(_pItem->dwItemClass & (ITEM_CLASS_UNIQUE | ITEM_CLASS_LEGEND | ITEM_CLASS_SET))
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Orb_Unique"), rand() % 2);
			else
				StringCbPrintf(_pItem->tszBufKey, sizeof(_pItem->tszBufKey), _T("%s%d"), _T("Item_Orb_Base"), rand() % 3);
		}
	}
}

void CItemMgr::CreateSize(Item* _pItem)
{
	if(_pItem->dwItemType & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS | ITEM_TYPE_SUB_WEAPON))
	{
		_pItem->iWidth = 1;
		_pItem->iHeight = 2;
	}
	else if(_pItem->dwItemType & (ITEM_TYPE_BELT | ITEM_TYPE_AMULET | ITEM_TYPE_RING | ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		_pItem->iWidth = 1;
		_pItem->iHeight = 1;
	}
}

void CItemMgr::CreateStat(Item* _pItem)
{
	if(_pItem->dwItemClass == 0)
	{
		if(_pItem->dwItemID & GEM_ID_TOPAZ1)
			_pItem->tMainStat.iStrength = 10;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ2)
			_pItem->tMainStat.iStrength = 20;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ3)
			_pItem->tMainStat.iStrength = 40;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ4)
			_pItem->tMainStat.iStrength = 80;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ5)
			_pItem->tMainStat.iStrength = 160;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE1)
			_pItem->tMainStat.iAgility = 10;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE2)
			_pItem->tMainStat.iAgility = 20;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE3)
			_pItem->tMainStat.iAgility = 40;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE4)
			_pItem->tMainStat.iAgility = 80;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE5)
			_pItem->tMainStat.iAgility = 160;
		else if(_pItem->dwItemID & GEM_ID_RUBY1)
			_pItem->tMainStat.iIntelligence = 10;
		else if(_pItem->dwItemID & GEM_ID_RUBY2)
			_pItem->tMainStat.iIntelligence = 20;
		else if(_pItem->dwItemID & GEM_ID_RUBY3)
			_pItem->tMainStat.iIntelligence = 40;
		else if(_pItem->dwItemID & GEM_ID_RUBY4)
			_pItem->tMainStat.iIntelligence = 80;
		else if(_pItem->dwItemID & GEM_ID_RUBY5)
			_pItem->tMainStat.iIntelligence = 160;
		else if(_pItem->dwItemID & GEM_ID_EMERALD1)
			_pItem->tMainStat.iVitality = 10;
		else if(_pItem->dwItemID & GEM_ID_EMERALD2)
			_pItem->tMainStat.iVitality = 20;
		else if(_pItem->dwItemID & GEM_ID_EMERALD3)
			_pItem->tMainStat.iVitality = 40;
		else if(_pItem->dwItemID & GEM_ID_EMERALD4)
			_pItem->tMainStat.iVitality = 80;
		else if(_pItem->dwItemID & GEM_ID_EMERALD5)
			_pItem->tMainStat.iVitality = 160;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND1)
		{
			_pItem->tMainStat.iStrength = 8;
			_pItem->tMainStat.iAgility = 8;
		}
		else if(_pItem->dwItemID & GEM_ID_DIAMOND2)
		{
			_pItem->tMainStat.iStrength = 16;
			_pItem->tMainStat.iAgility = 16;
		}
		else if(_pItem->dwItemID & GEM_ID_DIAMOND3)
		{
			_pItem->tMainStat.iStrength = 32;
			_pItem->tMainStat.iAgility = 32;
		}
		else if(_pItem->dwItemID & GEM_ID_DIAMOND4)
		{
			_pItem->tMainStat.iStrength = 64;
			_pItem->tMainStat.iAgility = 64;
		}
		else if(_pItem->dwItemID & GEM_ID_DIAMOND5)
		{
			_pItem->tMainStat.iStrength = 128;
			_pItem->tMainStat.iAgility = 128;
		}
		else if(_pItem->dwItemID & GEM_ID_AMETHYST1)
		{
			_pItem->tMainStat.iIntelligence = 8;
			_pItem->tMainStat.iVitality = 8;
		}
		else if(_pItem->dwItemID & GEM_ID_AMETHYST2)
		{
			_pItem->tMainStat.iIntelligence = 16;
			_pItem->tMainStat.iVitality = 16;
		}
		else if(_pItem->dwItemID & GEM_ID_AMETHYST3)
		{
			_pItem->tMainStat.iIntelligence = 32;
			_pItem->tMainStat.iVitality = 32;
		}
		else if(_pItem->dwItemID & GEM_ID_AMETHYST4)
		{
			_pItem->tMainStat.iIntelligence = 64;
			_pItem->tMainStat.iVitality = 64;
		}
		else if(_pItem->dwItemID & GEM_ID_AMETHYST5)
		{
			_pItem->tMainStat.iIntelligence = 128;
			_pItem->tMainStat.iVitality = 128;
		}
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_NORMAL)
	{
		// MainStat
		int iRand = rand() % 4;
		if(iRand == 0)
			_pItem->tMainStat.iStrength = rand() % 10 + 1;
		else if(iRand == 1)
			_pItem->tMainStat.iAgility = rand() % 10 + 1;
		else if(iRand == 2)
			_pItem->tMainStat.iIntelligence = rand() % 10 + 1;
		else if(iRand == 3)
			_pItem->tMainStat.iVitality = rand() % 10 + 1;
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		// MainStat
		int iRand = rand() % 4;
		if(iRand == 0)
			_pItem->tMainStat.iStrength = rand() % 20 + 1;
		else if(iRand == 1)
			_pItem->tMainStat.iAgility = rand() % 20 + 1;
		else if(iRand == 2)
			_pItem->tMainStat.iIntelligence = rand() % 20 + 1;
		else if(iRand == 3)
			_pItem->tMainStat.iVitality = rand() % 20 + 1;

		// AttackStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tAttackStat.fReducedCooldownTime = (rand() % 30 + 1) / 1000.0f;
		else if(iRand == 1)
			_pItem->tAttackStat.fCriticalProbability = (rand() % 30 + 1) / 1000.0f;
		else if(iRand == 2)
			_pItem->tAttackStat.fCriticalDamage = (rand() % 50 + 1) / 1000.0f;
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		// MainStat
		int iRand = rand() % 4;
		if(iRand == 0)
			_pItem->tMainStat.iStrength = rand() % 40 + 1;
		else if(iRand == 1)
			_pItem->tMainStat.iAgility = rand() % 40 + 1;
		else if(iRand == 2)
			_pItem->tMainStat.iIntelligence = rand() % 40 + 1;
		else if(iRand == 3)
			_pItem->tMainStat.iVitality = rand() % 40 + 1;

		// AttackStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tAttackStat.fReducedCooldownTime = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 1)
			_pItem->tAttackStat.fCriticalProbability = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 2)
			_pItem->tAttackStat.fCriticalDamage = (rand() % 100 + 1) / 1000.0f;

		// DefenseStat
		iRand = rand() % 8;
		if(iRand == 0)
			_pItem->tDefenseStat.iPhysicalResistance = (rand() % 200 + 1);
		else if(iRand == 1)
			_pItem->tDefenseStat.iColdResistance = (rand() % 200 + 1);
		else if(iRand == 2)
			_pItem->tDefenseStat.iFlameResistance = (rand() % 200 + 1);
		else if(iRand == 3)
			_pItem->tDefenseStat.iLightningResistance = (rand() % 200 + 1);
		else if(iRand == 4)
			_pItem->tDefenseStat.iPoisonResistance = (rand() % 200 + 1);
		else if(iRand == 5)
			_pItem->tDefenseStat.iHolyResistance = (rand() % 200 + 1);
		else if(iRand == 6)
			_pItem->tDefenseStat.fReducedNearDamage = (rand() % 30 + 1) / 1000.0f;
		else if(iRand == 7)
			_pItem->tDefenseStat.fReducedFarDamage = (rand() % 30 + 1) / 1000.0f;
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		// MainStat
		int iRand = rand() % 4;
		if(iRand == 0)
			_pItem->tMainStat.iStrength = rand() % 80;
		else if(iRand == 1)
			_pItem->tMainStat.iAgility = rand() % 80;
		else if(iRand == 2)
			_pItem->tMainStat.iIntelligence = rand() % 80;
		else if(iRand == 3)
			_pItem->tMainStat.iVitality = rand() % 80;

		// AttackStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tAttackStat.fReducedCooldownTime = (rand() % 70) / 1000.0f;
		else if(iRand == 1)
			_pItem->tAttackStat.fCriticalProbability = (rand() % 70) / 1000.0f;
		else if(iRand == 2)
			_pItem->tAttackStat.fCriticalDamage = (rand() % 200) / 1000.0f;

		// DefenseStat
		iRand = rand() % 8;
		if(iRand == 0)
			_pItem->tDefenseStat.iPhysicalResistance = (rand() % 200 + 1);
		else if(iRand == 1)
			_pItem->tDefenseStat.iColdResistance = (rand() % 500 + 1);
		else if(iRand == 2)
			_pItem->tDefenseStat.iFlameResistance = (rand() % 500 + 1);
		else if(iRand == 3)
			_pItem->tDefenseStat.iLightningResistance = (rand() % 500 + 1);
		else if(iRand == 4)
			_pItem->tDefenseStat.iPoisonResistance = (rand() % 500 + 1);
		else if(iRand == 5)
			_pItem->tDefenseStat.iHolyResistance = (rand() % 500 + 1);
		else if(iRand == 6)
			_pItem->tDefenseStat.fReducedNearDamage = (rand() % 40 + 1) / 1000.0f;
		else if(iRand == 7)
			_pItem->tDefenseStat.fReducedFarDamage = (rand() % 40 + 1) / 1000.0f;

		// LifeStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tLifeStat.fRestoresBonus = (rand() % 100 + 1) / 1000.0f;
		else if(iRand == 1)
			_pItem->tLifeStat.iLifeRecoveryOfSecond = rand() % 100 + 1;
		else if(iRand == 2)
			_pItem->tLifeStat.iLifeRecoveryOfHit = rand() % 100 + 1;
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_SET)
	{
		// MainStat
		int iRand = rand() % 4;
		if(iRand == 0)
			_pItem->tMainStat.iStrength = rand() % 160;
		else if(iRand == 1)
			_pItem->tMainStat.iAgility = rand() % 160;
		else if(iRand == 2)
			_pItem->tMainStat.iIntelligence = rand() % 160;
		else if(iRand == 3)
			_pItem->tMainStat.iVitality = rand() % 160;

		// AttackStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tAttackStat.fReducedCooldownTime = (rand() % 90) / 1000.0f;
		else if(iRand == 1)
			_pItem->tAttackStat.fCriticalProbability = (rand() % 90) / 1000.0f;
		else if(iRand == 2)
			_pItem->tAttackStat.fCriticalDamage = (rand() % 400) / 1000.0f;

		// DefenseStat
		iRand = rand() % 8;
		if(iRand == 0)
			_pItem->tDefenseStat.iPhysicalResistance = (rand() % 1000 + 1);
		else if(iRand == 1)
			_pItem->tDefenseStat.iColdResistance = (rand() % 1000 + 1);
		else if(iRand == 2)
			_pItem->tDefenseStat.iFlameResistance = (rand() % 1000 + 1);
		else if(iRand == 3)
			_pItem->tDefenseStat.iLightningResistance = (rand() % 1000 + 1);
		else if(iRand == 4)
			_pItem->tDefenseStat.iPoisonResistance = (rand() % 1000 + 1);
		else if(iRand == 5)
			_pItem->tDefenseStat.iHolyResistance = (rand() % 1000 + 1);
		else if(iRand == 6)
			_pItem->tDefenseStat.fReducedNearDamage = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 7)
			_pItem->tDefenseStat.fReducedFarDamage = (rand() % 50 + 1) / 1000.0f;

		// LifeStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tLifeStat.fRestoresBonus = (rand() % 200 + 1) / 1000.0f;
		else if(iRand == 1)
			_pItem->tLifeStat.iLifeRecoveryOfSecond = rand() % 200 + 1;
		else if(iRand == 2)
			_pItem->tLifeStat.iLifeRecoveryOfHit = rand() % 200 + 1;

		// ResourceStat
		iRand = rand() % 12;
		if(iRand == 0)
			_pItem->tResourceStat.iControlRecoveryOfSecond = rand() % 3 + 1;
		else if(iRand == 1)
			_pItem->tResourceStat.iEffortRecoveryOfSecond = rand() % 3 + 1;
		else if(iRand == 2)
			_pItem->tResourceStat.iHateRecoveryOfSecond = rand() % 8 + 1;
		else if(iRand == 3)
			_pItem->tResourceStat.iManaRecoveryOfSecond = rand() % 20 + 1;
		else if(iRand == 4)
			_pItem->tResourceStat.iRageRecoveryOfSecond = rand() % 2 + 1;
		else if(iRand == 5)
			_pItem->tResourceStat.iVisionRecoveryOfSecond = rand() % 5 + 1;
		else if(iRand == 6)
			_pItem->tResourceStat.fReducedControlConsumption = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 7)
			_pItem->tResourceStat.fReducedEffortConsumption = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 8)
			_pItem->tResourceStat.fReducedHateConsumption = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 9)
			_pItem->tResourceStat.fReducedManaConsumption = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 10)
			_pItem->tResourceStat.fReducedRageConsumption = (rand() % 50 + 1) / 1000.0f;
		else if(iRand == 11)
			_pItem->tResourceStat.fReducedVisionConsumption = (rand() % 50 + 1) / 1000.0f;

		// AdventureStat
		iRand = rand() % 3;
		if(iRand == 0)
			_pItem->tAdventureStat.fExperience = (rand() % 100 + 1) / 1000.0f;
		else if(iRand == 1)
			_pItem->tAdventureStat.fMagicItemsFound = (rand() % 100 + 1) / 1000.0f;
		else if(iRand == 2)
			_pItem->tAdventureStat.fDiscoveryOfGoldCoins = (rand() % 100 + 1) / 1000.0f;
	}
}

void CItemMgr::CreateValue(Item* _pItem)
{
	float fCoef = (rand() % 40 + 80) / 100.0f;

	// 목걸이
	if(_pItem->dwItemType & ITEM_TYPE_AMULET)
	{
		if(_pItem->dwItemID & AMULET_ID_AMULET)
		{
			_pItem->iDef = int(fCoef * _pItem->iLevel * 2.0f);
			_pItem->iValue = _pItem->iLevel * 100;
		}
	}
	// 반지
	else if(_pItem->dwItemType & ITEM_TYPE_RING)
	{
		if(_pItem->dwItemID & RING_ID_RING)
		{
			_pItem->iDef = int(fCoef * _pItem->iLevel * 2.0f);
			_pItem->iValue = _pItem->iLevel * 100;
		}
	}
	// 보석
	else if(_pItem->dwItemType & ITEM_TYPE_GEM)
	{
		if(_pItem->dwItemID & GEM_ID_TOPAZ1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_TOPAZ5)
			_pItem->iValue = 155000;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_SAPPHIRE5)
			_pItem->iValue = 155000;
		else if(_pItem->dwItemID & GEM_ID_RUBY1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_RUBY2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_RUBY3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_RUBY4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_RUBY5)
			_pItem->iValue = 155000;
		else if(_pItem->dwItemID & GEM_ID_EMERALD1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_EMERALD2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_EMERALD3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_EMERALD4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_EMERALD5)
			_pItem->iValue = 155000;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_DIAMOND5)
			_pItem->iValue = 155000;
		else if(_pItem->dwItemID & GEM_ID_AMETHYST1)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & GEM_ID_AMETHYST2)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & GEM_ID_AMETHYST3)
			_pItem->iValue = 25000;
		else if(_pItem->dwItemID & GEM_ID_AMETHYST4)
			_pItem->iValue = 75000;
		else if(_pItem->dwItemID & GEM_ID_AMETHYST5)
			_pItem->iValue = 155000;
	}
	// 재료
	else if(_pItem->dwItemType & ITEM_TYPE_MATERIAL)
	{
		if(_pItem->dwItemID & MATERIAL_ID_IRON)
			_pItem->iValue = 1000;
		else if(_pItem->dwItemID & MATERIAL_ID_CRYSTAL)
			_pItem->iValue = 3000;
		else if(_pItem->dwItemID & MATERIAL_ID_PATTERNS)
			_pItem->iValue = 3000;
		else if(_pItem->dwItemID & MATERIAL_ID_DIAMOND)
			_pItem->iValue = 5000;
		else if(_pItem->dwItemID & MATERIAL_ID_MANA_SOURCE)
			_pItem->iValue = 10000;
		else if(_pItem->dwItemID & MATERIAL_ID_ADAMANTIUM)
			_pItem->iValue = 10000;
		else if(_pItem->dwItemID & MATERIAL_ID_METAL_STAIN)
			_pItem->iValue = 10000;
	}
	// 신발
	if(_pItem->dwItemType & ITEM_TYPE_BOOTS)
	{
		if(_pItem->dwItemID & BOOTS_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & BOOTS_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & BOOTS_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & BOOTS_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & BOOTS_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 장갑
	else if(_pItem->dwItemType & ITEM_TYPE_GLOVES)
	{
		if(_pItem->dwItemID & GLOVES_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & GLOVES_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & GLOVES_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & GLOVES_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & GLOVES_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 모자
	else if(_pItem->dwItemType & ITEM_TYPE_HELMS)
	{
		if(_pItem->dwItemID & HELMS_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & HELMS_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & HELMS_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & HELMS_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & HELMS_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 바지
	else if(_pItem->dwItemType & ITEM_TYPE_PANTS)
	{
		if(_pItem->dwItemID & PANTS_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 15.0f);
		else if(_pItem->dwItemID & PANTS_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & PANTS_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & PANTS_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 5.0f);
		else if(_pItem->dwItemID & PANTS_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 5.0f);

		_pItem->iValue = _pItem->iLevel * 120;
	}
	// 어깨보호대
	else if(_pItem->dwItemType & ITEM_TYPE_SHOULDERS)
	{
		if(_pItem->dwItemID & SHOULDERS_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & SHOULDERS_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & SHOULDERS_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & SHOULDERS_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & SHOULDERS_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 벨트
	else if(_pItem->dwItemType & ITEM_TYPE_BELT)
	{
		if(_pItem->dwItemID & BELT_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & BELT_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & BELT_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & BELT_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & BELT_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 손목보호대
	else if(_pItem->dwItemType & ITEM_TYPE_BRACERS)
	{
		if(_pItem->dwItemID & BRACERS_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 10.0f);
		else if(_pItem->dwItemID & BRACERS_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 6.0f);
		else if(_pItem->dwItemID & BRACERS_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 8.0f);
		else if(_pItem->dwItemID & BRACERS_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);
		else if(_pItem->dwItemID & BRACERS_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 3.0f);

		_pItem->iValue = _pItem->iLevel * 110;
	}
	// 흉갑
	else if(_pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		if(_pItem->dwItemID & CHESTARMOR_ID_BARBARIAN)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 30.0f);
		else if(_pItem->dwItemID & CHESTARMOR_ID_DEMONHUNTER)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 25.0f);
		else if(_pItem->dwItemID & CHESTARMOR_ID_MONK)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 28.0f);
		else if(_pItem->dwItemID & CHESTARMOR_ID_WITCHDOCTOR)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 20.0f);
		else if(_pItem->dwItemID & CHESTARMOR_ID_WIZARD)
			_pItem->iDef = int(fCoef * _pItem->iLevel * 20.0f);

		_pItem->iValue = _pItem->iLevel * 120;
	}
	// 무기
	else if(_pItem->dwItemType & (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON))
	{
		if(_pItem->dwItemID & WEAPON_ID_AXE)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_BOW)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_CEREMONIAL_DAGGER)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_FIST)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_HANDXBOW)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_MACE)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_POLEARM)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_QUIVER)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 10.0f);
			_pItem->iValue = _pItem->iLevel * 120;
		}
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY1H)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_MIGHTY2H)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_SHIELD)
		{
			_pItem->iDef = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 120;
		}
		else if(_pItem->dwItemID & WEAPON_ID_SPEAR)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_STAFF)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_SWORD)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_AXE)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_MACE)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_TWO_HAND_SWORD)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 45.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_WAND)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 150;
		}
		else if(_pItem->dwItemID & WEAPON_ID_MOJO)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 10.0f);
			_pItem->iValue = _pItem->iLevel * 120;
		}
		else if(_pItem->dwItemID & WEAPON_ID_CROSSBOW)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 30.0f);
			_pItem->iValue = _pItem->iLevel * 170;
		}
		else if(_pItem->dwItemID & WEAPON_ID_ORB)
		{
			_pItem->iAtt = int(fCoef * _pItem->iLevel * 10.0f);
			_pItem->iValue = _pItem->iLevel * 120;
		}
	}
}