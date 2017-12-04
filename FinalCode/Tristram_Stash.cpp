#include "StdAfx.h"
#include "Tristram_Stash.h"

CTristram_Stash::CTristram_Stash(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_Stash"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 10.0f, 0.0f), 30.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_STASH;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("º¸°üÇÔ"));

	// Width
	m_fWidth = 100.0f;

	// Height
	m_fHeight = 50.0f;

	// Depth
	m_fDepth = 100.0f;
}

CTristram_Stash::~CTristram_Stash()
{
	Release();
}

void CTristram_Stash::Initialize()
{
	CStaticProb::Initialize();
}

int CTristram_Stash::Update()
{
	CStaticProb::Update();

	return 0;
}

void CTristram_Stash::Render()
{
	CStaticProb::Render();
}

void CTristram_Stash::Release()
{
}

void CTristram_Stash::Event()
{
	// StorageWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteLeftWindow();

		CObject* pWindow = new CStorageWindow(_T("StorageWindow"), OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);
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

void CTristram_Stash::EventEnd()
{
}