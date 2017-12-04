#include "StdAfx.h"
#include "SlotWindow.h"

CSlotWindow::CSlotWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Slot"))
{
	// SlotButton
	ZeroMemory(m_pSlotButton, sizeof(m_pSlotButton));

	// CooldownEnergy
	ZeroMemory(m_pCooldownEnergy, sizeof(m_pCooldownEnergy));

	// InterfaceMessage
	ZeroMemory(m_pInterfaceMessage, sizeof(m_pInterfaceMessage));
	
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.8426f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.3385f, 0.3148f, 0.0f);
}

CSlotWindow::~CSlotWindow()
{
	Release();
}

void CSlotWindow::Initialize()
{
	CWindowUI::Initialize();

	CTransformCom* pTransformCom;

	// SkillWindowButton(0)
	CBasicButton* pSkillWindowButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_SkillWindow"), _T("Button_Over_SkillWindow"), _T("Button_Down_SkillWindow"));
	m_pLayer->AddObject(pSkillWindowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pSkillWindowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.205f, -0.9055f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.1f, 0.0f);
	pSkillWindowButton->Initialize();
	AddButton(pSkillWindowButton);

	// InvenWindowButton(1)
	CBasicButton* pInvenWindowButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_InvenWindow"), _T("Button_Over_InvenWindow"), _T("Button_Down_InvenWindow"));
	m_pLayer->AddObject(pInvenWindowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pInvenWindowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.233f, -0.9055f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.1f, 0.0f);
	pInvenWindowButton->Initialize();
	AddButton(pInvenWindowButton);

	// QuestWindowButton(2)
	CBasicButton* pQuestWindowButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_QuestWindow"), _T("Button_Over_QuestWindow"), _T("Button_Down_QuestWindow"));
	m_pLayer->AddObject(pQuestWindowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pQuestWindowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.261f, -0.9055f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.1f, 0.0f);
	pQuestWindowButton->Initialize();
	AddButton(pQuestWindowButton);

	// AchieveWindowButton(3)
	CBasicButton* pAchieveWindowButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_AchieveWindow"), _T("Button_Over_AchieveWindow"), _T("Button_Down_AchieveWindow"));
	m_pLayer->AddObject(pAchieveWindowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pAchieveWindowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.290f, -0.9055f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.1f, 0.0f);
	pAchieveWindowButton->Initialize();
	AddButton(pAchieveWindowButton);

	// SettingWindowButton(4)
	CBasicButton* pSettingWindowButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_SettingWindow"), _T("Button_Over_SettingWindow"), _T("Button_Down_SettingWindow"));
	m_pLayer->AddObject(pSettingWindowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pSettingWindowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.318f, -0.9055f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.1f, 0.0f);
	pSettingWindowButton->Initialize();
	AddButton(pSettingWindowButton);

	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());
	if(pAccount != NULL)
	{
		// LifeEnergy
		CEnergyUI* pEnergyUI = new CLifeEnergy(NULL, OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
		pEnergyUI->Initialize();
		m_EnergyVec.push_back(pEnergyUI);

		// JobEnergy
		if(pAccount->info.iJob == 0)
		{
			pEnergyUI = new CRageEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);
		}
		else if(pAccount->info.iJob == 1)
		{
			pEnergyUI = new CHateEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);

			pEnergyUI = new CControlEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);
		}
		else if(pAccount->info.iJob == 2)
		{
			pEnergyUI = new CEffortEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);
		}
		else if(pAccount->info.iJob == 3)
		{
			pEnergyUI = new CManaEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);
		}
		else if(pAccount->info.iJob == 4)
		{
			pEnergyUI = new CVisionEnergy(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
			pEnergyUI->Initialize();
			m_EnergyVec.push_back(pEnergyUI);
		}

		// ExpEnergy
		pEnergyUI = new CExpEnergy(NULL, OBJ_TYPE_STATIC);
		m_pLayer->AddObject(pEnergyUI, LAYER_TYPE_UI);
		pEnergyUI->Initialize();
		m_EnergyVec.push_back(pEnergyUI);
	}

	Renew();
}

int CSlotWindow::Update()
{
	CWindowUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;

	for(size_t i = 0; i < m_ButtonVec.size(); ++i)
	{
		pUpdateCom = (CUpdateCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF8;

		pRenderCom = (CRenderCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000007;
	}

	for(size_t i = 0; i < m_EnergyVec.size(); ++i)
	{
		pUpdateCom = (CUpdateCom*)m_EnergyVec[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF8;

		pRenderCom = (CRenderCom*)m_EnergyVec[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000009;
	}

	for(int i = 0; i < 7; ++i)
	{
		pUpdateCom = (CUpdateCom*)m_pSlotButton[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF8;

		pRenderCom = (CRenderCom*)m_pSlotButton[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000007;
	}

	// Escape
	if(CInputMgr::GetInstance()->KeyDown(DIK_ESCAPE))
	{
		for(int i = 1; i < WINDOW_TYPE_END; ++i)
		{
			if(CUIMgr::GetInstance()->GetWindow((WINDOW_TYPE)i) != NULL)
			{
				CUIMgr::GetInstance()->DeleteWindow((WINDOW_TYPE)i);
				CInputMgr::GetInstance()->KeyStop(DIK_ESCAPE);
			}
		}
	}

	// FollowerWindow
	if(CInputMgr::GetInstance()->KeyDown(DIK_F))
	{
		// Find Follower
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Follower"), LAYER_TYPE_FOLLOWER);

		if(pFindObject != NULL)
		{
			if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER) == NULL)
			{
				CUIMgr::GetInstance()->DeleteCenterWindow();
				CUIMgr::GetInstance()->DeleteLeftWindow();

				CFollowerWindow* pFollowerWindow = new CFollowerWindow(_T("FollowerWindow"), OBJ_TYPE_STATIC);
				m_pLayer->AddObject(pFollowerWindow, LAYER_TYPE_UI);
				pFollowerWindow->Initialize();
			}
			else
			{
				CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_FOLLOWER);
				CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_FOLLOWER_DETAIL);
			}
		}
	}

	// SkillWIndow
	if(m_ButtonVec[0]->IsOver())
	{
		if(m_pInterfaceMessage[0] == NULL)
		{
			m_pInterfaceMessage[0] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Interface"), _T("기술(S)"));
			m_pLayer->AddObject(m_pInterfaceMessage[0], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pInterfaceMessage[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(0.205f, -0.75f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.124375f, 0.0844444f, 0.0f);

			m_pInterfaceMessage[0]->Initialize();
		}
	}
	else
	{
		if(m_pInterfaceMessage[0] != NULL)
		{
			m_pInterfaceMessage[0]->Destroy();
			m_pInterfaceMessage[0] = NULL;
		}
	}

	if(m_ButtonVec[0]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_S))
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_SKILL) == NULL)
			CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_SKILL);
		else
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_SKILL);
	}

	// InvenWindow
	if(m_ButtonVec[1]->IsOver())
	{
		if(m_pInterfaceMessage[1] == NULL)
		{
			m_pInterfaceMessage[1] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Interface"), _T("소지품(I)"));
			m_pLayer->AddObject(m_pInterfaceMessage[1], LAYER_TYPE_UI);

			CTransformCom* pTransformComA = (CTransformCom*)m_pInterfaceMessage[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComA->m_vPos = D3DXVECTOR3(0.233f, -0.75f, 0.0f);
			pTransformComA->m_vSize = D3DXVECTOR3(0.138438f, 0.0844444f, 0.0f);

			m_pInterfaceMessage[1]->Initialize();
		}
	}
	else
	{
		if(m_pInterfaceMessage[1] != NULL)
		{
			m_pInterfaceMessage[1]->Destroy();
			m_pInterfaceMessage[1] = NULL;
		}
	}

	if(m_ButtonVec[1]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_I))
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY) == NULL)
		{
			CUIMgr::GetInstance()->DeleteCenterWindow();
			CUIMgr::GetInstance()->DeleteRightWindow();

			CInvenWindow* pInvenWindow = new CInvenWindow(_T("InventoryWindow"), OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pInvenWindow, LAYER_TYPE_UI);
			pInvenWindow->Initialize();
		}
		else
		{
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_INVENTORY);
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_DETAIL);
		}
	}

	// QuestWindow
	if(m_ButtonVec[2]->IsOver())
	{
		if(m_pInterfaceMessage[2] == NULL)
		{
			m_pInterfaceMessage[2] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Interface"), _T("퀘스트(J)"));
			m_pLayer->AddObject(m_pInterfaceMessage[2], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pInterfaceMessage[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(0.261f, -0.75f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.143125f, 0.0844444f, 0.0f);

			m_pInterfaceMessage[2]->Initialize();
		}
	}
	else
	{
		if(m_pInterfaceMessage[2] != NULL)
		{
			m_pInterfaceMessage[2]->Destroy();
			m_pInterfaceMessage[2] = NULL;
		}
	}

	if(m_ButtonVec[2]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_J))
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_QUEST) == NULL)
		{
			CUIMgr::GetInstance()->DeleteCenterWindow();
			CUIMgr::GetInstance()->DeleteLeftWindow();

			CQuestWindow* pQuestWindow = new CQuestWindow(_T("QuestWindow"), OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pQuestWindow, LAYER_TYPE_UI);
			pQuestWindow->Initialize();
		}
		else
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_QUEST);
	}

	// AchieveWindow
	if(m_ButtonVec[3]->IsOver())
	{
		if(m_pInterfaceMessage[3] == NULL)
		{
			m_pInterfaceMessage[3] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Interface"), _T("업적(Y)"));
			m_pLayer->AddObject(m_pInterfaceMessage[3], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pInterfaceMessage[3]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(0.290f, -0.75f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.124375f, 0.0844444f, 0.0f);

			m_pInterfaceMessage[3]->Initialize();
		}
	}
	else
	{
		if(m_pInterfaceMessage[3] != NULL)
		{
			m_pInterfaceMessage[3]->Destroy();
			m_pInterfaceMessage[3] = NULL;
		}
	}

	if(m_ButtonVec[3]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_Y))
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_ACHIEVE) == NULL)
		{
			CUIMgr::GetInstance()->DeleteCenterWindow();
			CUIMgr::GetInstance()->DeleteLeftWindow();

			CAchieveWindow* pAchieveWindow = new CAchieveWindow(_T("AchieveWindow"), OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pAchieveWindow, LAYER_TYPE_UI);
			pAchieveWindow->Initialize();
		}
		else
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_ACHIEVE);
	}

	// SettingWindow
	if(m_ButtonVec[4]->IsOver())
	{
		if(m_pInterfaceMessage[4] == NULL)
		{
			m_pInterfaceMessage[4] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Interface"), _T("게임메뉴(Esc)"));
			m_pLayer->AddObject(m_pInterfaceMessage[4], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pInterfaceMessage[4]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(0.318f, -0.75f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.2025f, 0.0844444f, 0.0f);

			m_pInterfaceMessage[4]->Initialize();
		}
	}
	else
	{
		if(m_pInterfaceMessage[4] != NULL)
		{
			m_pInterfaceMessage[4]->Destroy();
			m_pInterfaceMessage[4] = NULL;
		}
	}

	if(m_ButtonVec[4]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_ESCAPE))
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_SETTING) == NULL)
			CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_SETTING);
		else
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_SETTING);
	}

	for(int i = 0; i < 6; ++i)
	{
		if(m_pSlotButton[i]->IsRUp())
		{
			switch(m_pSlotButton[i]->GetSlotType())
			{
			case SLOT_TYPE_BARBARIAN_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_PRIMARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_SECONDARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_MIGHT:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_MIGHT, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_TACTICS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_TACTICS, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_RAGE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_RAGE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_SECONDARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_DEFENSIVE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_HUNTING:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_HUNTING, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_DEVICES:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_ARCHERY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_ARCHERY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_PRIMARY:						
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_PRIMARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_SECONDARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_DEFENSIVE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_TECHNIQUES:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_TECHNIQUES, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_FOCUS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_FOCUS, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_MANTRAS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_MANTRAS, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_PRIMARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_SECONDARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_TERROR:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_TERROR, i, m_pSlotButton[i]->GetSlotID());	
				break;
			case SLOT_TYPE_WITCHDOCTOR_DECAY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_DECAY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_VOODOO:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_VOODOO, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_PRIMARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_SECONDARY, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_DEFENSIVE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_FORCE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_FORCE, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_CONJURATION:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_CONJURATION, i, m_pSlotButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_MASTERY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_MASTERY, i, m_pSlotButton[i]->GetSlotID());
				break;
			}
		}
	}

	return 0;
}

void CSlotWindow::Render()
{
	CWindowUI::Render();
}

void CSlotWindow::Release()
{
	// EnergyVec
	for(size_t i = 0; i < m_EnergyVec.size(); ++i)
	{
		m_EnergyVec[i]->Destroy();
		m_EnergyVec[i] = NULL;
	}
	m_EnergyVec.clear();

	// SlotButton
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlotButton[i] != NULL)
		{
			m_pSlotButton[i]->Destroy();
			m_pSlotButton[i] = NULL;
		}
	}

	// CooldownEnergy
	for(int i = 0; i < 7; ++i)
	{
		if(m_pCooldownEnergy[i] != NULL)
		{
			m_pCooldownEnergy[i]->Destroy();
			m_pCooldownEnergy[i] = NULL;
		}
	}

	// InterfaceMessage
	for(int i = 0; i < 5; ++i)
	{
		if(m_pInterfaceMessage[i] != NULL)
		{
			m_pInterfaceMessage[i]->Destroy();
			m_pInterfaceMessage[i] = NULL;
		}
	}
}

void CSlotWindow::Renew()
{
	// SlotButton Clear
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlotButton[i] != NULL)
		{
			m_pSlotButton[i]->Destroy();
			m_pSlotButton[i] = NULL;
		}
	}

	// CooldownEnergy
	for(int i = 0; i < 7; ++i)
	{
		if(m_pCooldownEnergy[i] != NULL)
		{
			m_pCooldownEnergy[i]->Destroy();
			m_pCooldownEnergy[i] = NULL;
		}
	}

	// InterfaceMessage Clear
	for(int i = 0; i < 5; ++i)
	{
		if(m_pInterfaceMessage[i] != NULL)
		{
			m_pInterfaceMessage[i]->Destroy();
			m_pInterfaceMessage[i] = NULL;
		}
	}

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// SlotButton
	for(int i = 0; i < 7; ++i)
	{
		CSlot* pSlot = ((CPlayer*)pPlayer)->GetSlot(i);

		m_pSlotButton[i] = new CSlotButton(NULL, OBJ_TYPE_STATIC, pSlot->GetSlotType(), pSlot->GetSlotID());
		m_pLayer->AddObject(m_pSlotButton[i], LAYER_TYPE_UI);

		CTransformCom* pTransformCom = (CTransformCom*)m_pSlotButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.3154f + 0.0702f * i, -0.9062f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0594f, 0.1018f, 0.0f);

		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pSlotButton[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF8;

		CRenderCom* pRenderCom = (CRenderCom*)m_pSlotButton[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000007;

		m_pSlotButton[i]->Initialize();
	}

	// CooldownEnergy
	for(int i = 0; i < 7; ++i)
	{
		CSlot* pSlot = ((CPlayer*)pPlayer)->GetSlot(i);

		m_pCooldownEnergy[i] = new CCooldownEnergy(NULL, OBJ_TYPE_STATIC, pSlot);
		m_pLayer->AddObject(m_pCooldownEnergy[i], LAYER_TYPE_UI);

		CTransformCom* pTransformCom = (CTransformCom*)m_pCooldownEnergy[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.3154f + 0.0702f * i, -0.9062f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0594f, 0.1018f, 0.0f);

		m_pCooldownEnergy[i]->Initialize();
	}
}