#include "StdAfx.h"
#include "GateWay.h"

CGateWay::CGateWay(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, GATE_WAY_TYPE _eGateWayType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_GateWay"));

	// ProbType
	m_eProbType = PROB_TYPE_GATE_WAY;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("게이트웨이"));

	// Width
	m_fWidth = 200.0f;

	// Height
	m_fHeight = 10.0f;

	// Depth
	m_fDepth = 200.0f;

	// GateWayType
	m_eGateWayType = _eGateWayType;
}

CGateWay::~CGateWay()
{
	Release();
}

void CGateWay::Initialize()
{
	CStaticProb::Initialize();

	/*
	// TransformCom
	CTransformCom* pTransformCom;

	// FireEffect0
	CFireEffect* pFireEffect0 = new CFireEffect(NULL, OBJ_TYPE_DYNAMIC, NULL, _T("Effect_Fire_Diff"), _T("Effect_Fire_Alpha"), _T("Effect_Fire_Noise"));
	m_pLayer->AddObject(pFireEffect0, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFireEffect0->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-75.0f, 66.0f, 48.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	pFireEffect0->Initialize();

	// FireEffect1
	CFireEffect* pFireEffect1 = new CFireEffect(NULL, OBJ_TYPE_DYNAMIC, NULL, _T("Effect_Fire_Diff"), _T("Effect_Fire_Alpha"), _T("Effect_Fire_Noise"));
	m_pLayer->AddObject(pFireEffect1, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFireEffect1->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(7.0f, 66.0f, -84.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	pFireEffect1->Initialize();

	// FireEffect2
	CFireEffect* pFireEffect2 = new CFireEffect(NULL, OBJ_TYPE_DYNAMIC, NULL, _T("Effect_Fire_Diff"), _T("Effect_Fire_Alpha"), _T("Effect_Fire_Noise"));
	m_pLayer->AddObject(pFireEffect2, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFireEffect2->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(75.0f, 50.0f, 52.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	pFireEffect2->Initialize();
	*/
}

int CGateWay::Update()
{
	CStaticProb::Update();

	return 0;
}

void CGateWay::Render()
{
	CStaticProb::Render();
}

void CGateWay::Release()
{
	
}

void CGateWay::Event()
{
	if(CDataMgr::GetInstance()->IsGateWay(m_eGateWayType) == false)
		CDataMgr::GetInstance()->AddGateWay(m_eGateWayType);

	// GateWayWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_GATE_WAY) == NULL)
	{
		CUIMgr::GetInstance()->DeleteCenterWindow();
		CUIMgr::GetInstance()->DeleteLeftWindow();

		CObject* pGateWayWindow = new CGateWayWindow(_T("GateWayWindow"), OBJ_TYPE_DYNAMIC, m_eGateWayType);
		m_pLayer->AddObject(pGateWayWindow, LAYER_TYPE_UI);
		pGateWayWindow->Initialize();
	}
}

void CGateWay::EventEnd()
{
	
}