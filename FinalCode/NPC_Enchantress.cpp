#include "StdAfx.h"
#include "NPC_Enchantress.h"

CNPC_Enchantress::CNPC_Enchantress(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("Enchantress_Base"));

	// DynamicMesh
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[0];
	pDynamicMesh->m_pAnimController->SetAnimation(59);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_ENCHANTRESS;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("¿ä¼ú»ç"));

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;
}

CNPC_Enchantress::~CNPC_Enchantress()
{
	Release();
}

void CNPC_Enchantress::Initialize()
{
	CNPC::Initialize();
}

int CNPC_Enchantress::Update()
{
	CNPC::Update();

	return 0;
}

void CNPC_Enchantress::Render()
{
	CNPC::Render();
}

void CNPC_Enchantress::Release()
{
}

void CNPC_Enchantress::Event()
{
	CNPC::Event();

	CEnchantressMessage* pEnchantressMessage = new CEnchantressMessage(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer->AddObject(pEnchantressMessage, LAYER_TYPE_UI);
	pEnchantressMessage->Initialize();
}

void CNPC_Enchantress::EventEnd()
{
	CNPC::EventEnd();
}

void CNPC_Enchantress::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);
}