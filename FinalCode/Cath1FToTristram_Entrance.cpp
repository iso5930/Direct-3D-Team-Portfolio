#include "StdAfx.h"
#include "Cath1FToTristram_Entrance.h"

CCath1FToTristram_Entrance::CCath1FToTristram_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CDynamicProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Door"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_CATH1F_TO_TRISTRAM_DOOR;

	// Mode
	m_iMode = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(6374.0f, 0.0f, 1816.0f);

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.0f, 0.5f, 1.0f);
}

CCath1FToTristram_Entrance::~CCath1FToTristram_Entrance()
{
	Release();
}

void CCath1FToTristram_Entrance::Initialize()
{
	CDynamicProb::Initialize();
}

int CCath1FToTristram_Entrance::Update()
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

void CCath1FToTristram_Entrance::Render()
{
}

void CCath1FToTristram_Entrance::Release()
{
}

void CCath1FToTristram_Entrance::Event()
{
	// Mode
	m_iMode = 1;

	// SetAnimation
	m_pDynamicMesh->m_pAnimController->SetAnimation(3);

	// RemoveComponent
	RemoveComponent(COM_TYPE_COLLISION);

	// Cath1FToTristram_Gate
	CGate* pCath1FToTristram_Gate = new CGate(NULL, OBJ_TYPE_DYNAMIC, _T("트리스트럼"), _T("Tristram"), &D3DXVECTOR3(5605.6f, 695.88f, 23559.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), PLAYSCENE_TYPE_TRISTRAM);
	m_pLayer->AddObject(pCath1FToTristram_Gate, LAYER_TYPE_STATIC_PROB);
	CTransformCom* pTransformCom = (CTransformCom*)pCath1FToTristram_Gate->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(6374.0f, 0.0f, 1816.0f);
	pCath1FToTristram_Gate->SetSize(14.0f, 195.0f, 272.0f);
	pCath1FToTristram_Gate->Initialize();
}

void CCath1FToTristram_Entrance::EventEnd()
{
}

void CCath1FToTristram_Entrance::Mode0()
{
}

void CCath1FToTristram_Entrance::Mode1()
{
	if(m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.25 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		// Mode
		++m_iMode;

		// SetAnimation
		m_pDynamicMesh->m_pAnimController->SetAnimation(2);
	}
}