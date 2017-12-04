#include "StdAfx.h"
#include "Tristram_BlackSmith.h"

CTristram_BlackSmith::CTristram_BlackSmith(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Blacksmith"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_BLACKSMITH;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("블랙스미스"));

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;
}

CTristram_BlackSmith::~CTristram_BlackSmith()
{
	Release();
}

void CTristram_BlackSmith::Initialize()
{
	CNPC::Initialize();
}

int CTristram_BlackSmith::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_BlackSmith::Render()
{
	CNPC::Render();
}

void CTristram_BlackSmith::Release()
{
}

void CTristram_BlackSmith::Event()
{
	CNPC::Event();

	// FactoryWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteLeftWindow();

		CObject* pWindow = new CFactoryWindow(_T("FactoryWindow"), OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);
		pWindow->Initialize();

		// Axe
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Axe
			Formula* pFormula_Axe;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Axe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_AXE, rand() % 5 + 5));
				pFormula_Axe->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Axe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_AXE, rand() % 5 + 5));
				pFormula_Axe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Axe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_AXE, rand() % 5 + 5));
				pFormula_Axe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Axe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_AXE, rand() % 5 + 5));
				pFormula_Axe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Axe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_AXE, rand() % 5 + 5));
				pFormula_Axe->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddAxeFormula(pFormula_Axe);
		}

		// Bow
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Bow
			Formula* pFormula_Bow;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Bow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_BOW, rand() % 5 + 5));
				pFormula_Bow->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Bow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_BOW, rand() % 5 + 5));
				pFormula_Bow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Bow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_BOW, rand() % 5 + 5));
				pFormula_Bow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Bow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_BOW, rand() % 5 + 5));
				pFormula_Bow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Bow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_BOW, rand() % 5 + 5));
				pFormula_Bow->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddBowFormula(pFormula_Bow);
		}

		// CeremonialDagger
		for(int i = 0; i < 10; ++i)
		{
			// Formula_CeremonialDagger
			Formula* pFormula_CeremonialDagger;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_CeremonialDagger = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_CEREMONIAL_DAGGER, rand() % 5 + 5));
				pFormula_CeremonialDagger->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_CeremonialDagger = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_CEREMONIAL_DAGGER, rand() % 5 + 5));
				pFormula_CeremonialDagger->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_CeremonialDagger = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_CEREMONIAL_DAGGER, rand() % 5 + 5));
				pFormula_CeremonialDagger->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_CeremonialDagger = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_CEREMONIAL_DAGGER, rand() % 5 + 5));
				pFormula_CeremonialDagger->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_CeremonialDagger = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_CEREMONIAL_DAGGER, rand() % 5 + 5));
				pFormula_CeremonialDagger->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddCeremonialDaggerFormula(pFormula_CeremonialDagger);
		}

		// Fist
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Fist
			Formula* pFormula_Fist;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Fist = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_FIST, rand() % 5 + 5));
				pFormula_Fist->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Fist = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_FIST, rand() % 5 + 5));
				pFormula_Fist->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Fist = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_FIST, rand() % 5 + 5));
				pFormula_Fist->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Fist = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_FIST, rand() % 5 + 5));
				pFormula_Fist->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Fist = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_FIST, rand() % 5 + 5));
				pFormula_Fist->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddFistFormula(pFormula_Fist);
		}

		// HandXBow
		for(int i = 0; i < 10; ++i)
		{
			// Formula_HandXBow
			Formula* pFormula_HandXBow;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_HandXBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_HANDXBOW, rand() % 5 + 5));
				pFormula_HandXBow->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_HandXBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_HANDXBOW, rand() % 5 + 5));
				pFormula_HandXBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_HandXBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_HANDXBOW, rand() % 5 + 5));
				pFormula_HandXBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_HandXBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_HANDXBOW, rand() % 5 + 5));
				pFormula_HandXBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_HandXBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_HANDXBOW, rand() % 5 + 5));
				pFormula_HandXBow->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddHandXBowFormula(pFormula_HandXBow);
		}

		// Mace
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Mace
			Formula* pFormula_Mace;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Mace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MACE, rand() % 5 + 5));
				pFormula_Mace->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Mace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MACE, rand() % 5 + 5));
				pFormula_Mace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Mace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MACE, rand() % 5 + 5));
				pFormula_Mace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Mace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MACE, rand() % 5 + 5));
				pFormula_Mace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Mace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MACE, rand() % 5 + 5));
				pFormula_Mace->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddMaceFormula(pFormula_Mace);
		}

		// Polearm
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Polearm
			Formula* pFormula_Polearm;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Polearm = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_POLEARM, rand() % 5 + 5));
				pFormula_Polearm->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Polearm = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_POLEARM, rand() % 5 + 5));
				pFormula_Polearm->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Polearm = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_POLEARM, rand() % 5 + 5));
				pFormula_Polearm->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Polearm = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_POLEARM, rand() % 5 + 5));
				pFormula_Polearm->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Polearm = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_POLEARM, rand() % 5 + 5));
				pFormula_Polearm->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddPolearmFormula(pFormula_Polearm);
		}

		// Quiver
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Quiver
			Formula* pFormula_Quiver;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Quiver = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_QUIVER, rand() % 5 + 5));
				pFormula_Quiver->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Quiver = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_QUIVER, rand() % 5 + 5));
				pFormula_Quiver->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Quiver = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_QUIVER, rand() % 5 + 5));
				pFormula_Quiver->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Quiver = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_QUIVER, rand() % 5 + 5));
				pFormula_Quiver->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Quiver = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_QUIVER, rand() % 5 + 5));
				pFormula_Quiver->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddQuiverFormula(pFormula_Quiver);
		}

		// Mighty1H
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Mighty1H
			Formula* pFormula_Mighty1H;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Mighty1H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MIGHTY1H, rand() % 5 + 5));
				pFormula_Mighty1H->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Mighty1H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MIGHTY1H, rand() % 5 + 5));
				pFormula_Mighty1H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Mighty1H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MIGHTY1H, rand() % 5 + 5));
				pFormula_Mighty1H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Mighty1H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MIGHTY1H, rand() % 5 + 5));
				pFormula_Mighty1H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Mighty1H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MIGHTY1H, rand() % 5 + 5));
				pFormula_Mighty1H->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddMighty1HFormula(pFormula_Mighty1H);
		}

		// Mighty2H
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Mighty2H
			Formula* pFormula_Mighty2H;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Mighty2H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_MIGHTY2H, rand() % 5 + 5));
				pFormula_Mighty2H->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Mighty2H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_MIGHTY2H, rand() % 5 + 5));
				pFormula_Mighty2H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Mighty2H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_MIGHTY2H, rand() % 5 + 5));
				pFormula_Mighty2H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Mighty2H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_MIGHTY2H, rand() % 5 + 5));
				pFormula_Mighty2H->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Mighty2H = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_MIGHTY2H, rand() % 5 + 5));
				pFormula_Mighty2H->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddMighty2HFormula(pFormula_Mighty2H);
		}

		// Shield
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Shield
			Formula* pFormula_Shield;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Shield = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SHIELD, rand() % 5 + 5));
				pFormula_Shield->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Shield = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SHIELD, rand() % 5 + 5));
				pFormula_Shield->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Shield = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SHIELD, rand() % 5 + 5));
				pFormula_Shield->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Shield = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SHIELD, rand() % 5 + 5));
				pFormula_Shield->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Shield = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SHIELD, rand() % 5 + 5));
				pFormula_Shield->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddShieldFormula(pFormula_Shield);
		}

		// Spear
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Spear
			Formula* pFormula_Spear;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Spear = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SPEAR, rand() % 5 + 5));
				pFormula_Spear->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Spear = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SPEAR, rand() % 5 + 5));
				pFormula_Spear->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Spear = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SPEAR, rand() % 5 + 5));
				pFormula_Spear->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Spear = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SPEAR, rand() % 5 + 5));
				pFormula_Spear->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Spear = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SPEAR, rand() % 5 + 5));
				pFormula_Spear->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddSpearFormula(pFormula_Spear);
		}

		// Staff
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Staff
			Formula* pFormula_Staff;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Staff = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_STAFF, rand() % 5 + 5));
				pFormula_Staff->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Staff = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_STAFF, rand() % 5 + 5));
				pFormula_Staff->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Staff = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_STAFF, rand() % 5 + 5));
				pFormula_Staff->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Staff = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_STAFF, rand() % 5 + 5));
				pFormula_Staff->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Staff = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_STAFF, rand() % 5 + 5));
				pFormula_Staff->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddStaffFormula(pFormula_Staff);
		}

		// Sword
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Sword
			Formula* pFormula_Sword;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Sword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SWORD, rand() % 5 + 5));
				pFormula_Sword->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Sword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SWORD, rand() % 5 + 5));
				pFormula_Sword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Sword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SWORD, rand() % 5 + 5));
				pFormula_Sword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Sword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SWORD, rand() % 5 + 5));
				pFormula_Sword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Sword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_SWORD, rand() % 5 + 5));
				pFormula_Sword->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddSwordFormula(pFormula_Sword);
		}

		// TwoHandAxe
		for(int i = 0; i < 10; ++i)
		{
			// Formula_TwoHandAxe
			Formula* pFormula_TwoHandAxe;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_TwoHandAxe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_AXE, rand() % 5 + 5));
				pFormula_TwoHandAxe->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_TwoHandAxe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_AXE, rand() % 5 + 5));
				pFormula_TwoHandAxe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_TwoHandAxe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_AXE, rand() % 5 + 5));
				pFormula_TwoHandAxe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_TwoHandAxe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_AXE, rand() % 5 + 5));
				pFormula_TwoHandAxe->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_TwoHandAxe = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_AXE, rand() % 5 + 5));
				pFormula_TwoHandAxe->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddTwoHandAxeFormula(pFormula_TwoHandAxe);
		}

		// TwoHandMace
		for(int i = 0; i < 10; ++i)
		{
			// Formula_TwoHandMace
			Formula* pFormula_TwoHandMace;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_TwoHandMace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_MACE, rand() % 5 + 5));
				pFormula_TwoHandMace->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_TwoHandMace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_MACE, rand() % 5 + 5));
				pFormula_TwoHandMace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_TwoHandMace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_MACE, rand() % 5 + 5));
				pFormula_TwoHandMace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_TwoHandMace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_MACE, rand() % 5 + 5));
				pFormula_TwoHandMace->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_TwoHandMace = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_MACE, rand() % 5 + 5));
				pFormula_TwoHandMace->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddTwoHandMaceFormula(pFormula_TwoHandMace);
		}

		// TwoHandSword
		for(int i = 0; i < 10; ++i)
		{
			// Formula_TwoHandSword
			Formula* pFormula_TwoHandSword;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_TwoHandSword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_SWORD, rand() % 5 + 5));
				pFormula_TwoHandSword->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_TwoHandSword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_SWORD, rand() % 5 + 5));
				pFormula_TwoHandSword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_TwoHandSword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_SWORD, rand() % 5 + 5));
				pFormula_TwoHandSword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_TwoHandSword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_SWORD, rand() % 5 + 5));
				pFormula_TwoHandSword->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_TwoHandSword = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_TWO_HAND_SWORD, rand() % 5 + 5));
				pFormula_TwoHandSword->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddTwoHandSwordFormula(pFormula_TwoHandSword);
		}

		// Wand
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Wand
			Formula* pFormula_Wand;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Wand = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_WAND, rand() % 5 + 5));
				pFormula_Wand->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Wand = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_WAND, rand() % 5 + 5));
				pFormula_Wand->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Wand = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_WAND, rand() % 5 + 5));
				pFormula_Wand->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Wand = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_WAND, rand() % 5 + 5));
				pFormula_Wand->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Wand = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON, WEAPON_ID_WAND, rand() % 5 + 5));
				pFormula_Wand->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddWandFormula(pFormula_Wand);
		}

		// Mojo
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Mojo
			Formula* pFormula_Mojo;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Mojo = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MOJO, rand() % 5 + 5));
				pFormula_Mojo->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Mojo = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MOJO, rand() % 5 + 5));
				pFormula_Mojo->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Mojo = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MOJO, rand() % 5 + 5));
				pFormula_Mojo->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Mojo = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MOJO, rand() % 5 + 5));
				pFormula_Mojo->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Mojo = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_MOJO, rand() % 5 + 5));
				pFormula_Mojo->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddMojoFormula(pFormula_Mojo);
		}

		// CrossBow
		for(int i = 0; i < 10; ++i)
		{
			// Formula_CrossBow
			Formula* pFormula_CrossBow;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_CrossBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_CROSSBOW, rand() % 5 + 5));
				pFormula_CrossBow->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_CrossBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_CROSSBOW, rand() % 5 + 5));
				pFormula_CrossBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_CrossBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_CROSSBOW, rand() % 5 + 5));
				pFormula_CrossBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_CrossBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_CROSSBOW, rand() % 5 + 5));
				pFormula_CrossBow->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_CrossBow = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_MAIN_WEAPON, WEAPON_ID_CROSSBOW, rand() % 5 + 5));
				pFormula_CrossBow->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddCrossBowFormula(pFormula_CrossBow);
		}

		// Orb
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Orb
			Formula* pFormula_Orb;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Orb = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_ORB, rand() % 5 + 5));
				pFormula_Orb->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Orb = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_ORB, rand() % 5 + 5));
				pFormula_Orb->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Orb = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_ORB, rand() % 5 + 5));
				pFormula_Orb->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Orb = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_ORB, rand() % 5 + 5));
				pFormula_Orb->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Orb = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_SUB_WEAPON, WEAPON_ID_ORB, rand() % 5 + 5));
				pFormula_Orb->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddOrbFormula(pFormula_Orb);
		}

		// Helms
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Helms
			Formula* pFormula_Helms;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Helms = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_HELMS, 0, rand() % 5 + 5));
				pFormula_Helms->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Helms = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_HELMS, 0, rand() % 5 + 5));
				pFormula_Helms->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Helms = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_HELMS, 0, rand() % 5 + 5));
				pFormula_Helms->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Helms = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_HELMS, 0, rand() % 5 + 5));
				pFormula_Helms->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Helms = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_HELMS, 0, rand() % 5 + 5));
				pFormula_Helms->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddHelmsFormula(pFormula_Helms);
		}

		// Shoulders
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Shoulders
			Formula* pFormula_Shoulders;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Shoulders = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_SHOULDERS, 0, rand() % 5 + 5));
				pFormula_Shoulders->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Shoulders = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_SHOULDERS, 0, rand() % 5 + 5));
				pFormula_Shoulders->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Shoulders = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_SHOULDERS, 0, rand() % 5 + 5));
				pFormula_Shoulders->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Shoulders = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_SHOULDERS, 0, rand() % 5 + 5));
				pFormula_Shoulders->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Shoulders = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_SHOULDERS, 0, rand() % 5 + 5));
				pFormula_Shoulders->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddShouldersFormula(pFormula_Shoulders);
		}

		// ChestArmor
		for(int i = 0; i < 10; ++i)
		{
			// Formula_ChestArmor
			Formula* pFormula_ChestArmor;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_ChestArmor = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_CHESTARMOR, 0, rand() % 5 + 5));
				pFormula_ChestArmor->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_ChestArmor = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_CHESTARMOR, 0, rand() % 5 + 5));
				pFormula_ChestArmor->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_ChestArmor = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_CHESTARMOR, 0, rand() % 5 + 5));
				pFormula_ChestArmor->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_ChestArmor = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_CHESTARMOR, 0, rand() % 5 + 5));
				pFormula_ChestArmor->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_ChestArmor = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_CHESTARMOR, 0, rand() % 5 + 5));
				pFormula_ChestArmor->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddChestArmorFormula(pFormula_ChestArmor);
		}

		// Bracers
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Bracers
			Formula* pFormula_Bracers;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Bracers = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_BRACERS, 0, rand() % 5 + 5));
				pFormula_Bracers->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Bracers = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_BRACERS, 0, rand() % 5 + 5));
				pFormula_Bracers->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Bracers = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_BRACERS, 0, rand() % 5 + 5));
				pFormula_Bracers->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Bracers = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_BRACERS, 0, rand() % 5 + 5));
				pFormula_Bracers->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Bracers = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_BRACERS, 0, rand() % 5 + 5));
				pFormula_Bracers->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddBracersFormula(pFormula_Bracers);
		}

		// Gloves
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Gloves
			Formula* pFormula_Gloves;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Gloves = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_GLOVES, 0, rand() % 5 + 5));
				pFormula_Gloves->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Gloves = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_GLOVES, 0, rand() % 5 + 5));
				pFormula_Gloves->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Gloves = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_GLOVES, 0, rand() % 5 + 5));
				pFormula_Gloves->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Gloves = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_GLOVES, 0, rand() % 5 + 5));
				pFormula_Gloves->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Gloves = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_GLOVES, 0, rand() % 5 + 5));
				pFormula_Gloves->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddGlovesFormula(pFormula_Gloves);
		}

		// Belt
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Belt
			Formula* pFormula_Belt;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Belt = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_BELT, 0, rand() % 5 + 5));
				pFormula_Belt->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Belt = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_BELT, 0, rand() % 5 + 5));
				pFormula_Belt->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Belt = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_BELT, 0, rand() % 5 + 5));
				pFormula_Belt->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Belt = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_BELT, 0, rand() % 5 + 5));
				pFormula_Belt->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Belt = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_BELT, 0, rand() % 5 + 5));
				pFormula_Belt->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddBeltFormula(pFormula_Belt);
		}

		// Pants
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Pants
			Formula* pFormula_Pants;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Pants = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_PANTS, 0, rand() % 5 + 5));
				pFormula_Pants->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Pants = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_PANTS, 0, rand() % 5 + 5));
				pFormula_Pants->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Pants = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_PANTS, 0, rand() % 5 + 5));
				pFormula_Pants->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Pants = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_PANTS, 0, rand() % 5 + 5));
				pFormula_Pants->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Pants = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_PANTS, 0, rand() % 5 + 5));
				pFormula_Pants->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddPantsFormula(pFormula_Pants);
		}

		// Boots
		for(int i = 0; i < 10; ++i)
		{
			// Formula_Boots
			Formula* pFormula_Boots;

			// ItemClass
			int iRand = rand() % 100;
			if(iRand >= 98)
			{
				pFormula_Boots = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_SET, ITEM_TYPE_BOOTS, 0, rand() % 5 + 5));
				pFormula_Boots->SetMaterial(rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2, rand() % 3 + 2);
			}
			else if(iRand >= 90)
			{
				pFormula_Boots = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_LEGEND, ITEM_TYPE_BOOTS, 0, rand() % 5 + 5));
				pFormula_Boots->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
			}
			else if(iRand >= 75)
			{
				pFormula_Boots = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_UNIQUE, ITEM_TYPE_BOOTS, 0, rand() % 5 + 5));
				pFormula_Boots->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0);
			}
			else if(iRand >= 50)
			{
				pFormula_Boots = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_MAGIC, ITEM_TYPE_BOOTS, 0, rand() % 5 + 5));
				pFormula_Boots->SetMaterial(rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1, 0, 0, 0, 0);
			}
			else
			{
				pFormula_Boots = new Formula(CItemMgr::GetInstance()->CreateItem(ITEM_CLASS_NORMAL, ITEM_TYPE_BOOTS, 0, rand() % 5 + 5));
				pFormula_Boots->SetMaterial(rand() % 2 + 1, 0, 0, 0, 0, 0, 0);
			}

			((CFactoryWindow*)pWindow)->AddBootsFormula(pFormula_Boots);
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

void CTristram_BlackSmith::EventEnd()
{
	CNPC::EventEnd();
}

void CTristram_BlackSmith::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);
}