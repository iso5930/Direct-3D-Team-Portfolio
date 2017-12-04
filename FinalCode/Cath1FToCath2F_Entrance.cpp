#include "StdAfx.h"
#include "Cath1FToCath2F_Entrance.h"

CCath1FToCath2F_Entrance::CCath1FToCath2F_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Door"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_CATH1F_TO_CATH2F_DOOR;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(1534.2f, -583.53f, 13391.0f);

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.0f, 0.5f, 1.0f);
}

CCath1FToCath2F_Entrance::~CCath1FToCath2F_Entrance()
{
	Release();
}

void CCath1FToCath2F_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CCath1FToCath2F_Entrance::Update()
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

void CCath1FToCath2F_Entrance::Render()
{
}

void CCath1FToCath2F_Entrance::Release()
{
}

void CCath1FToCath2F_Entrance::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(3);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);

	// Cath1FToCath2F_Gate
	CGate* pCath1FToCath2F_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("대성당 지하 2층"), _T("Cathedral_F2"), &D3DXVECTOR3(12896.0f, 19.49f, 8008.2f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_CATHEDRAL_F2);
	m_pLayer->AddObject(pCath1FToCath2F_Gate, LAYER_TYPE_STATIC_PROB);
	CTransformCom* pTransformCom = (CTransformCom*)pCath1FToCath2F_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(1534.2f, -583.53f, 13391.0f);
	pCath1FToCath2F_Gate->SetSize(14.0f, 195.0f, 272.0f);
	pCath1FToCath2F_Gate->Initialize();
}

void CCath1FToCath2F_Entrance::EventEnd()
{
}

void CCath1FToCath2F_Entrance::Mode0()
{
}

void CCath1FToCath2F_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}