#include "StdAfx.h"
#include "TristramToCath1F_Entrance.h"

CTristramToCath1F_Entrance::CTristramToCath1F_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_WoodDoor"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_TO_CATH1F_DOOR;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(5635.9f, 723.845f, 22674.7f);
}

CTristramToCath1F_Entrance::~CTristramToCath1F_Entrance()
{
	Release();
}

void CTristramToCath1F_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CTristramToCath1F_Entrance::Update()
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

void CTristramToCath1F_Entrance::Render()
{
}

void CTristramToCath1F_Entrance::Release()
{
}

void CTristramToCath1F_Entrance::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(3);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);
}

void CTristramToCath1F_Entrance::EventEnd()
{
}

void CTristramToCath1F_Entrance::Mode0()
{
}

void CTristramToCath1F_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}