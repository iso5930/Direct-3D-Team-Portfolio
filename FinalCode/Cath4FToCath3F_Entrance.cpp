#include "StdAfx.h"
#include "Cath4FToCath3F_Entrance.h"

CCath4FToCath3F_Entrance::CCath4FToCath3F_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Door"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_CATH4F_TO_CATH3F_DOOR;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(9810.0f, 43.0f, 2139.0f);

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.0f, 0.5f, 1.0f);
}

CCath4FToCath3F_Entrance::~CCath4FToCath3F_Entrance()
{
	Release();
}

void CCath4FToCath3F_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CCath4FToCath3F_Entrance::Update()
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

void CCath4FToCath3F_Entrance::Render()
{
}

void CCath4FToCath3F_Entrance::Release()
{
}

void CCath4FToCath3F_Entrance::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(3);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);
}

void CCath4FToCath3F_Entrance::EventEnd()
{
}

void CCath4FToCath3F_Entrance::Mode0()
{
}

void CCath4FToCath3F_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}