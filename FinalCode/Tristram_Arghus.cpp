#include "StdAfx.h"
#include "Tristram_Arghus.h"

CTristram_Arghus::CTristram_Arghus(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Arghus"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_ARGHUS;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("아그너스"));

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;
}

CTristram_Arghus::~CTristram_Arghus()
{
	Release();
}

void CTristram_Arghus::Initialize()
{
	CNPC::Initialize();
}

int CTristram_Arghus::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_Arghus::Render()
{
	CNPC::Render();
}

void CTristram_Arghus::Release()
{
}

void CTristram_Arghus::Event()
{
	CNPC::Event();

	// StoreWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORE) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteLeftWindow();

		// 상점
		CObject* pWindow = new CStoreWindow(_T("StoreWindow"), OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);

		// Weapon
		for(int i = 0; i < 10; ++i)
		{
			// Item_Weapon
			Item* pItem_Weapon;

			// ItemType
			DWORD dwItemType = 0;
			int iRand = rand() % 3;
			if(iRand == 0)
				dwItemType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON;
			else if(iRand == 1)
				dwItemType = ITEM_TYPE_MAIN_WEAPON;
			else if(iRand == 2)
				dwItemType = ITEM_TYPE_SUB_WEAPON;

			// ItemClass
			iRand = rand() % 100;
			if(iRand >= 98)
				pItem_Weapon = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 90)
				pItem_Weapon = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 75)
				pItem_Weapon = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 50)
				pItem_Weapon = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, dwItemType, 0, rand() % 5 + 5);
			else
				pItem_Weapon = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, dwItemType, 0, rand() % 5 + 5);

			((CStoreWindow*)pWindow)->AddWeapon(pItem_Weapon);
		}

		// Armor
		for(int i = 0; i < 10; ++i)
		{
			// Item_Armor
			Item* pItem_Armor;

			// ItemType
			DWORD dwItemType = 0;
			int iRand = rand() % 8;
			if(iRand == 0)
				dwItemType = ITEM_TYPE_HELMS;
			else if(iRand == 1)
				dwItemType = ITEM_TYPE_SHOULDERS;
			else if(iRand == 2)
				dwItemType = ITEM_TYPE_CHESTARMOR;
			else if(iRand == 3)
				dwItemType = ITEM_TYPE_BRACERS;
			else if(iRand == 4)
				dwItemType = ITEM_TYPE_GLOVES;
			else if(iRand == 5)
				dwItemType = ITEM_TYPE_BELT;
			else if(iRand == 6)
				dwItemType = ITEM_TYPE_PANTS;
			else if(iRand == 7)
				dwItemType = ITEM_TYPE_BOOTS;

			// ItemClass
			iRand = rand() % 100;
			if(iRand >= 98)
				pItem_Armor = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 90)
				pItem_Armor = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 75)
				pItem_Armor = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 50)
				pItem_Armor = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, dwItemType, 0, rand() % 5 + 5);
			else
				pItem_Armor = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, dwItemType, 0, rand() % 5 + 5);

			((CStoreWindow*)pWindow)->AddArmor(pItem_Armor);
		}

		// Accessory
		for(int i = 0; i < 10; ++i)
		{
			// Item_Accessory
			Item* pItem_Accessory;

			// ItemType
			DWORD dwItemType = 0;
			int iRand = rand() % 2;
			if(iRand == 0)
				dwItemType = ITEM_TYPE_AMULET;
			else if(iRand == 1)
				dwItemType = ITEM_TYPE_RING;

			// ItemClass
			iRand = rand() % 100;
			if(iRand >= 98)
				pItem_Accessory = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 90)
				pItem_Accessory = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 75)
				pItem_Accessory = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, dwItemType, 0, rand() % 5 + 5);
			else if(iRand >= 50)
				pItem_Accessory = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, dwItemType, 0, rand() % 5 + 5);
			else
				pItem_Accessory = CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, dwItemType, 0, rand() % 5 + 5);

			((CStoreWindow*)pWindow)->AddAccessory(pItem_Accessory);
		}

		((CStoreWindow*)pWindow)->SetPuzzleAccessoryLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleBeltLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleBootsLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleBracersLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleChestArmorLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleGlovesLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleHelmLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzlePantsLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleShoulderLevel(rand() % 5 + 5);
		((CStoreWindow*)pWindow)->SetPuzzleWeaponLevel(rand() % 5 + 5);

		pWindow->Initialize();
	}

	// InvenWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteRightWindow();

		CObject* pWindow = new CInvenWindow(_T("InventoryWindow"), OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);
		pWindow->Initialize();
	}
	else
	{
		// PlaySoundForUI
		CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));
	}
}

void CTristram_Arghus::EventEnd()
{
	CNPC::EventEnd();
}

void CTristram_Arghus::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);
}