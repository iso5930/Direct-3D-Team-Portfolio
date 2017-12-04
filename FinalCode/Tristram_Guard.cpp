#include "StdAfx.h"
#include "Tristram_Guard.h"

CTristram_Guard::CTristram_Guard(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Guard"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_GUARD;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("경비병"));
}

CTristram_Guard::~CTristram_Guard()
{
	Release();
}

void CTristram_Guard::Initialize()
{
	CNPC::Initialize();
}

int CTristram_Guard::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_Guard::Render()
{
	CNPC::Render();
}

void CTristram_Guard::Release()
{
}

void CTristram_Guard::Event()
{
	CNPC::Event();

	if(m_iMode == 0)
	{
		CConversationMessage* pConversationMessage = new CConversationMessage(NULL, OBJ_TYPE_DYNAMIC, _T("경비병"), _T("Sign_Guard1"));
		m_pLayer->AddObject(pConversationMessage, LAYER_TYPE_UI);
		pConversationMessage->Initialize();
	}
	else if(m_iMode == 1)
	{
		CMainQuest2_Message* pMainQuest2_Message = new CMainQuest2_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest2_Message, LAYER_TYPE_UI);
		pMainQuest2_Message->Initialize();
	}
	else if(m_iMode == 2)
	{
		CMainQuest2_1_Message* pMainQuest2_1_Message = new CMainQuest2_1_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest2_1_Message, LAYER_TYPE_UI);
		pMainQuest2_1_Message->Initialize();
	}
}

void CTristram_Guard::EventEnd()
{
	CNPC::EventEnd();
}

void CTristram_Guard::SetMode(int _iMode)
{
	CNPC::SetMode(_iMode);

	if(_iMode == 0)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 1)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 2)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
}