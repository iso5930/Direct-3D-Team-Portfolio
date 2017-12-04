#include "StdAfx.h"
#include "Tristram_Gate_Town.h"

CTristram_Gate_Town::CTristram_Gate_Town(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_Gate_Town"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, 200.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_GATE_TOWN;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(8017.0f, 299.0f, 5862.0f);
}

CTristram_Gate_Town::~CTristram_Gate_Town()
{
	Release();
}

void CTristram_Gate_Town::Initialize()
{
	CDynamicProb::Initialize();
}

int CTristram_Gate_Town::Update()
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

void CTristram_Gate_Town::Render()
{
	CDynamicProb::Render();
}

void CTristram_Gate_Town::Release()
{
}

void CTristram_Gate_Town::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(2);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);
}

void CTristram_Gate_Town::Mode0()
{
}

void CTristram_Gate_Town::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(1);
	}
}

void CTristram_Gate_Town::EventEnd()
{
}