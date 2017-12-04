#include "StdAfx.h"
#include "Tristram_Tashun.h"

CTristram_Tashun::CTristram_Tashun(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CNPC(_tszObjKey, _eObjType)
{
	// BufferCom
	m_pBufferCom->AddBuffer(_T("NPC_Tristram_Tashun"));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_NPC, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// NPCType
	m_eNPCType = NPC_TYPE_TRISTRAM_TASHUN;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));
}

CTristram_Tashun::~CTristram_Tashun()
{
	Release();
}

void CTristram_Tashun::Initialize()
{
	CNPC::Initialize();
}

int CTristram_Tashun::Update()
{
	CNPC::Update();

	return 0;
}

void CTristram_Tashun::Render()
{
	CNPC::Render();
}

void CTristram_Tashun::Release()
{
}

void CTristram_Tashun::Event()
{
	CNPC::Event();

	if(m_iMode == 0)
	{
		CConversationMessage* pConversationMessage = new CConversationMessage(NULL, OBJ_TYPE_DYNAMIC, _T("타스한"), _T("Sign_Tashun"));
		m_pLayer->AddObject(pConversationMessage, LAYER_TYPE_UI);
		pConversationMessage->Initialize();
	}
	else if(m_iMode == 1)
	{
		CMainQuest3_Message* pMainQuest3_Message = new CMainQuest3_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest3_Message, LAYER_TYPE_UI);
		pMainQuest3_Message->Initialize();
	}
	else if(m_iMode == 2)
	{
		CMainQuest4_Message* pMainQuest4_Message = new CMainQuest4_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest4_Message, LAYER_TYPE_UI);
		pMainQuest4_Message->Initialize();
	}
	else if(m_iMode == 3)
	{
		CMainQuest5_Message* pMainQuest5_Message = new CMainQuest5_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest5_Message, LAYER_TYPE_UI);
		pMainQuest5_Message->Initialize();
	}
	else if(m_iMode == 4)
	{
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

		CPlayer* pPlayer = (CPlayer*)pFindObject;
		if(pPlayer->GetStat()->iLevel >= 10)
		{
			CMainQuest6_Message* pMainQuest6_Message = new CMainQuest6_Message(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer->AddObject(pMainQuest6_Message, LAYER_TYPE_UI);
			pMainQuest6_Message->Initialize();
		}
		else
		{
			CConversationMessage* pConversationMessage = new CConversationMessage(NULL, OBJ_TYPE_DYNAMIC, _T("타스한"), _T("Sign_Tashun"));
			m_pLayer->AddObject(pConversationMessage, LAYER_TYPE_UI);
			pConversationMessage->Initialize();
		}
	}
	else if(m_iMode == 5)
	{
		CMainQuest7_Message* pMainQuest7_Message = new CMainQuest7_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest7_Message, LAYER_TYPE_UI);
		pMainQuest7_Message->Initialize();
	}
	else if(m_iMode == 6)
	{
		CMainQuest7_1_Message* pMainQuest7_1_Message = new CMainQuest7_1_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest7_1_Message, LAYER_TYPE_UI);
		pMainQuest7_1_Message->Initialize();
	}
	else if(m_iMode == 7)
	{
		CMainQuest8_Message* pMainQuest8_Message = new CMainQuest8_Message(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest8_Message, LAYER_TYPE_UI);
		pMainQuest8_Message->Initialize();
	}
	else if(m_iMode == 8)
	{
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

		CPlayer* pPlayer = (CPlayer*)pFindObject;
		if(pPlayer->GetStat()->iLevel >= 20)
		{
			CMainQuest9_Message* pMainQuest9_Message = new CMainQuest9_Message(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer->AddObject(pMainQuest9_Message, LAYER_TYPE_UI);
			pMainQuest9_Message->Initialize();
		}
		else
		{
			CConversationMessage* pConversationMessage = new CConversationMessage(NULL, OBJ_TYPE_DYNAMIC, _T("타스한"), _T("Sign_Tashun"));
			m_pLayer->AddObject(pConversationMessage, LAYER_TYPE_UI);
			pConversationMessage->Initialize();
		}
	}
}

void CTristram_Tashun::EventEnd()
{
	CNPC::EventEnd();
}

void CTristram_Tashun::SetMode(int _iMode)
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
	else if(_iMode == 3)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 4)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 5)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 6)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 7)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 8)
	{
		// Width & Height & Depth
		m_fWidth = 60.0f; m_fHeight = 100.0f; m_fDepth = 60.0f;
	}
	else if(_iMode == 9)
	{
		// Width & Height & Depth
		m_fWidth = 0.0f; m_fHeight = 0.0f; m_fDepth = 0.0f;
	}
}