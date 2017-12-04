#include "StdAfx.h"
#include "Tristram_Wagon_Destroyed.h"

CTristram_Wagon_Destroyed::CTristram_Wagon_Destroyed(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_Wagon_Destroyed"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PROB, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f), new Collision(0, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 30.0f, 50.0f));
	AddComponent(pCollisionCom);

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_WAGON_DESTROYED;
}

CTristram_Wagon_Destroyed::~CTristram_Wagon_Destroyed()
{
	Release();
}

void CTristram_Wagon_Destroyed::Initialize()
{
	CStaticProb::Initialize();
}

int CTristram_Wagon_Destroyed::Update()
{
	CStaticProb::Update();

	return 0;
}

void CTristram_Wagon_Destroyed::Render()
{
	CStaticProb::Render();
}

void CTristram_Wagon_Destroyed::Release()
{
}

void CTristram_Wagon_Destroyed::Event()
{
}

void CTristram_Wagon_Destroyed::EventEnd()
{
}