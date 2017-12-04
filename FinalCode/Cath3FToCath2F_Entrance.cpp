#include "StdAfx.h"
#include "Cath3FToCath2F_Entrance.h"

CCath3FToCath2F_Entrance::CCath3FToCath2F_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Door"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_CATH3F_TO_CATH2F_DOOR;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(6733.0f, 51.0f, 5215.0f);

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.0f, 0.5f, 1.0f);
}

CCath3FToCath2F_Entrance::~CCath3FToCath2F_Entrance()
{
	Release();
}

void CCath3FToCath2F_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CCath3FToCath2F_Entrance::Update()
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

void CCath3FToCath2F_Entrance::Render()
{
}

void CCath3FToCath2F_Entrance::Release()
{
}

void CCath3FToCath2F_Entrance::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(3);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);
}

void CCath3FToCath2F_Entrance::EventEnd()
{
}

void CCath3FToCath2F_Entrance::Mode0()
{
}

void CCath3FToCath2F_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}