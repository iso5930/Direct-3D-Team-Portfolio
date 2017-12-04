#include "StdAfx.h"
#include "Tristram_Mystic.h"

CTristram_Mystic::CTristram_Mystic(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Mystic"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_MYSTIC;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("미스티나"));

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;
}

CTristram_Mystic::~CTristram_Mystic()
{
	Release();
}

void CTristram_Mystic::Initialize()
{
	CNPC::Initialize();
}

int CTristram_Mystic::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_Mystic::Render()
{
	CNPC::Render();
}

void CTristram_Mystic::Release()
{
}

void CTristram_Mystic::Event()
{
	CNPC::Event();

	// Width
	m_fWidth = 0.0f;

	// Height
	m_fHeight = 0.0f;

	// Depth
	m_fDepth = 0.0f;

	// Quest
	CMainQuest1_Message* pMainQuest1_Message = new CMainQuest1_Message(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer->AddObject(pMainQuest1_Message, LAYER_TYPE_UI);
	pMainQuest1_Message->Initialize();

	// SetState
	SetState(new CTristram_Mystic_Talk);
}

void CTristram_Mystic::EventEnd()
{
	CNPC::EventEnd();

	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// SetState
	SetState(new CTristram_Mystic_Walk);
}

void CTristram_Mystic::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);
}