#include "StdAfx.h"
#include "Tristram_Jeweler.h"

CTristram_Jeweler::CTristram_Jeweler(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Jeweler"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_JEWELER;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("보석상"));

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;
}

CTristram_Jeweler::~CTristram_Jeweler()
{
	Release();
}

void CTristram_Jeweler::Initialize()
{
	CNPC::Initialize();
}

int CTristram_Jeweler::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_Jeweler::Render()
{
	CNPC::Render();
}

void CTristram_Jeweler::Release()
{
}

void CTristram_Jeweler::Event()
{
	CNPC::Event();

	// EnchantWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_ENCHANT) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteLeftWindow();

		CObject* pWindow = new CEnchantWindow(_T("EnchantWindow"), OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);
		pWindow->Initialize();

		// Topaz
		Formula* pFormula_Topaz2 = new Formula(new Item(_T("레벨2 토파즈"), _T("Item_Gems_2"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Topaz2->SetTopaz(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddTopaz(pFormula_Topaz2);

		Formula* pFormula_Topaz3 = new Formula(new Item(_T("레벨3 토파즈"), _T("Item_Gems_3"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Topaz3->SetTopaz(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddTopaz(pFormula_Topaz3);

		Formula* pFormula_Topaz4 = new Formula(new Item(_T("레벨4 토파즈"), _T("Item_Gems_4"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Topaz4->SetTopaz(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddTopaz(pFormula_Topaz4);

		Formula* pFormula_Topaz5 = new Formula(new Item(_T("레벨5 토파즈"), _T("Item_Gems_5"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Topaz5->SetTopaz(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddTopaz(pFormula_Topaz5);

		// Sappire
		Formula* pFormula_Sappire2 = new Formula(new Item(_T("레벨2 사파이어"), _T("Item_Gems_7"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Sappire2->SetSapphire(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddSapphire(pFormula_Sappire2);

		Formula* pFormula_Sappire3 = new Formula(new Item(_T("레벨3 사파이어"), _T("Item_Gems_8"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Sappire3->SetSapphire(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddSapphire(pFormula_Sappire3);

		Formula* pFormula_Sappire4 = new Formula(new Item(_T("레벨4 사파이어"), _T("Item_Gems_9"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Sappire4->SetSapphire(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddSapphire(pFormula_Sappire4);

		Formula* pFormula_Sappire5 = new Formula(new Item(_T("레벨5 사파이어"), _T("Item_Gems_10"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Sappire5->SetSapphire(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddSapphire(pFormula_Sappire5);

		// Ruby
		Formula* pFormula_Ruby2 = new Formula(new Item(_T("레벨2 루비"), _T("Item_Gems_12"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Ruby2->SetRuby(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddRuby(pFormula_Ruby2);

		Formula* pFormula_Ruby3 = new Formula(new Item(_T("레벨3 루비"), _T("Item_Gems_13"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Ruby3->SetRuby(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddRuby(pFormula_Ruby3);

		Formula* pFormula_Ruby4 = new Formula(new Item(_T("레벨4 루비"), _T("Item_Gems_14"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Ruby4->SetRuby(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddRuby(pFormula_Ruby4);

		Formula* pFormula_Ruby5 = new Formula(new Item(_T("레벨5 루비"), _T("Item_Gems_15"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Ruby5->SetRuby(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddRuby(pFormula_Ruby5);

		// Emerald
		Formula* pFormula_Emerald2 = new Formula(new Item(_T("레벨2 에메랄드"), _T("Item_Gems_17"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Emerald2->SetEmerald(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddEmerald(pFormula_Emerald2);

		Formula* pFormula_Emerald3 = new Formula(new Item(_T("레벨3 에메랄드"), _T("Item_Gems_18"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Emerald3->SetEmerald(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddEmerald(pFormula_Emerald3);

		Formula* pFormula_Emerald4 = new Formula(new Item(_T("레벨4 에메랄드"), _T("Item_Gems_19"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Emerald4->SetEmerald(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddEmerald(pFormula_Emerald4);

		Formula* pFormula_Emerald5 = new Formula(new Item(_T("레벨5 에메랄드"), _T("Item_Gems_20"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Emerald5->SetEmerald(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddEmerald(pFormula_Emerald5);

		// Diamond
		Formula* pFormula_Diamond2 = new Formula(new Item(_T("레벨2 다이아몬드"), _T("Item_Gems_22"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Diamond2->SetDiamond(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddDiamond(pFormula_Diamond2);

		Formula* pFormula_Diamond3 = new Formula(new Item(_T("레벨3 다이아몬드"), _T("Item_Gems_23"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Diamond3->SetDiamond(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddDiamond(pFormula_Diamond3);

		Formula* pFormula_Diamond4 = new Formula(new Item(_T("레벨4 다이아몬드"), _T("Item_Gems_24"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Diamond4->SetDiamond(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddDiamond(pFormula_Diamond4);

		Formula* pFormula_Diamond5 = new Formula(new Item(_T("레벨5 다이아몬드"), _T("Item_Gems_25"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Diamond5->SetDiamond(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddDiamond(pFormula_Diamond5);

		// Amethyst
		Formula* pFormula_Amethyst2 = new Formula(new Item(_T("레벨2 자수정"), _T("Item_Gems_27"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));
		pFormula_Amethyst2->SetAmethyst(3, 0, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddAmethyst(pFormula_Amethyst2);

		Formula* pFormula_Amethyst3 = new Formula(new Item(_T("레벨3 자수정"), _T("Item_Gems_28"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));
		pFormula_Amethyst3->SetAmethyst(0, 3, 0, 0, 0);
		((CEnchantWindow*)pWindow)->AddAmethyst(pFormula_Amethyst3);

		Formula* pFormula_Amethyst4 = new Formula(new Item(_T("레벨4 자수정"), _T("Item_Gems_29"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));
		pFormula_Amethyst4->SetAmethyst(0, 0, 3, 0, 0);
		((CEnchantWindow*)pWindow)->AddAmethyst(pFormula_Amethyst4);

		Formula* pFormula_Amethyst5 = new Formula(new Item(_T("레벨5 자수정"), _T("Item_Gems_30"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));
		pFormula_Amethyst5->SetAmethyst(0, 0, 0, 3, 0);
		((CEnchantWindow*)pWindow)->AddAmethyst(pFormula_Amethyst5);

		// Amulet
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Amulet
			Formula* pFormula_Amulet;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Amulet = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_AMULET, 0, rand() % 5 + 5));
				pFormula_Amulet->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Amulet = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_AMULET, 0, rand() % 5 + 5));
				pFormula_Amulet->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Amulet = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_AMULET, 0, rand() % 5 + 5));
				pFormula_Amulet->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Amulet = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_AMULET, 0, rand() % 5 + 5));
				pFormula_Amulet->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Amulet = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_AMULET, 0, rand() % 5 + 5));
				pFormula_Amulet->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CEnchantWindow*)pWindow)->AddAmulet(pFormula_Amulet);
		}

		// Ring
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Ring
			Formula* pFormula_Ring;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Ring = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_RING, 0, rand() % 5 + 5));
				pFormula_Ring->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Ring = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_RING, 0, rand() % 5 + 5));
				pFormula_Ring->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Ring = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_RING, 0, rand() % 5 + 5));
				pFormula_Ring->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Ring = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_RING, 0, rand() % 5 + 5));
				pFormula_Ring->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Ring = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_RING, 0, rand() % 5 + 5));
				pFormula_Ring->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CEnchantWindow*)pWindow)->AddRing(pFormula_Ring);
		}
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

void CTristram_Jeweler::EventEnd()
{
	CNPC::EventEnd();
}

void CTristram_Jeweler::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);
}