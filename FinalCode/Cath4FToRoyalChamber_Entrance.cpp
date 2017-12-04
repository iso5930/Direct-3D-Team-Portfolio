#include "StdAfx.h"
#include "Cath4FToRoyalChamber_Entrance.h"

CCath4FToRoyalChamber_Entrance::CCath4FToRoyalChamber_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Door"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_CATH4F_TO_ROYAL_CHAMBER;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("¿Õ°¡ÀÇ ¹¦½Ç"));

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(10459.0f, -152.0f, 10182.0f);

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// Width
	m_fWidth = 150.0f;

	// Height
	m_fHeight = 300.0f;

	// Depth
	m_fDepth = 150.0f;
}

CCath4FToRoyalChamber_Entrance::~CCath4FToRoyalChamber_Entrance()
{
	Release();
}

void CCath4FToRoyalChamber_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CCath4FToRoyalChamber_Entrance::Update()
{
	CDynamicProb::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;
	}

	return 0;
}

void CCath4FToRoyalChamber_Entrance::Render()
{
}

void CCath4FToRoyalChamber_Entrance::Release()
{
}

void CCath4FToRoyalChamber_Entrance::Event()
{
	// FindIndexVec
	vector<int> FindInexVec;
	CItemMgr::GetInstance()->FindItemInInven(FindInexVec, &Item(_T("¿­¼è"), _T("Item_Quest_6"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_6, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

	if(FindInexVec.size() != 0)
	{
		// Mode
		m_iMode = 1;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(3);

		// RemoveComponent
		RemoveComponent(COM_TYPE_COLLISION);

		// Cath4FToRoyalChamber_Gate
		CGate* pCath4FToRoyalChamber_Gate = new CGate(_T("StaticProb"), OBJ_TYPE_DYNAMIC, _T("¿Õ°¡ÀÇ ¹¦½Ç"), _T("RoyalChamber"), &D3DXVECTOR3(2063.0f, 6.0f, 1777.0f), &D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_ROYAL_CHAMBER);
		m_pLayer->AddObject(pCath4FToRoyalChamber_Gate, LAYER_TYPE_STATIC_PROB);

		CTransformCom* pTransformCom = (CTransformCom*)pCath4FToRoyalChamber_Gate->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(10459.0f, -152.0f, 10182.0f);

		pCath4FToRoyalChamber_Gate->SetSize(272.0f, 195.0f, 14.0f);
		pCath4FToRoyalChamber_Gate->Initialize();
		
		// Width & Height & Depth
		m_fWidth = 0.0f;
		m_fHeight = 0.0f;
		m_fDepth = 0.0f;
	}
	else
		CUIMgr::GetInstance()->CreateTextMessage(_T("¿­¼è°¡ ÇÊ¿äÇÕ´Ï´Ù."));
}

void CCath4FToRoyalChamber_Entrance::EventEnd()
{
}

void CCath4FToRoyalChamber_Entrance::Mode0()
{
}

void CCath4FToRoyalChamber_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}