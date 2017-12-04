#include "StdAfx.h"
#include "DemonHunterArcheryWindow.h"

CDemonHunterArcheryWindow::CDemonHunterArcheryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_DemonHunter_Archery"))
{
	// Select
	m_iSelect = -1;

	// Index
	m_iIndex = _iIndex;

	// SlotID
	m_eSlotID = _eSlotID;

	// Name
	SetRect(&m_rcName[0], 446, 212, 546, 262);
	SetRect(&m_rcName[1], 542, 212, 642, 262);
	SetRect(&m_rcName[2], 638, 212, 738, 262);
	SetRect(&m_rcName[3], 734, 212, 834, 262);
	_tcscpy_s(m_tszName[0], MIN_STR, _T("난사"));
	_tcscpy_s(m_tszName[1], MIN_STR, _T("다발 사격"));
	_tcscpy_s(m_tszName[2], MIN_STR, _T("확산탄"));
	_tcscpy_s(m_tszName[3], MIN_STR, _T("복수의 비"));

	// Level
	SetRect(&m_rcLevel[0], 446, 127, 546, 177);
	SetRect(&m_rcLevel[1], 542, 127, 642, 177);
	SetRect(&m_rcLevel[2], 638, 127, 738, 177);
	SetRect(&m_rcLevel[3], 734, 127, 834, 177);
	_tcscpy_s(m_tszLevel[0], MIN_STR, _T("19"));
	_tcscpy_s(m_tszLevel[1], MIN_STR, _T("22"));
	_tcscpy_s(m_tszLevel[2], MIN_STR, _T("27"));
	_tcscpy_s(m_tszLevel[3], MIN_STR, _T("30"));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.03f, 1.5782f, 0.0f);
}

CDemonHunterArcheryWindow::~CDemonHunterArcheryWindow()
{
	Release();
}

void CDemonHunterArcheryWindow::Initialize()
{
	CWindowUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

	// Stat
	Stat* pStat = ((CPlayer*)pPlayer)->GetStat();

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.477f, 0.851f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);

	// ConfirmButton(1)
	CBasicButton* pConfirmButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Confirm"), _T("Button_Over_Confirm"), _T("Button_Down_Confirm"));
	m_pLayer->AddObject(pConfirmButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pConfirmButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.13f, -0.485f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2444f, 0.0838f, 0.0f);
	pConfirmButton->Initialize();
	AddButton(pConfirmButton);

	// CancelButton(2)
	CBasicButton* pCancelButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cancel"), _T("Button_Over_Cancel"), _T("Button_Down_Cancel"));
	m_pLayer->AddObject(pCancelButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCancelButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.13f, -0.485f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2444f, 0.0838f, 0.0f);
	pCancelButton->Initialize();
	AddButton(pCancelButton);

	// LeftButton(3)
	CBasicButton* pLeftButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Left1"), _T("Button_Over_Left1"), _T("Button_Down_Left1"));
	m_pLayer->AddObject(pLeftButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pLeftButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.41f, 0.51f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0635f, 0.1482f, 0.0f);
	pLeftButton->Initialize();
	AddButton(pLeftButton);

	// RightButton(4)
	CBasicButton* pRightButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Right1"), _T("Button_Over_Right1"), _T("Button_Down_Right1"));
	m_pLayer->AddObject(pRightButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pRightButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.41f, 0.51f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0635f, 0.1482f, 0.0f);
	pRightButton->Initialize();
	AddButton(pRightButton);

	// SelectedSkillButton(5)
	CSkillButton* pSkillButton = new CSkillButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_END, m_eSlotID);
	m_pLayer->AddObject(pSkillButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pSkillButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.275f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
	pSkillButton->Initialize();
	AddButton(pSkillButton);

	// StrafeButton(6)
	CSlotButton* pStrafeButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_DEMONHUNTER_ARCHERY, SLOT_ID_DEMONHUNTER_STRAFE);
	m_pLayer->AddObject(pStrafeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pStrafeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.225f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pStrafeButton->Initialize();
	AddButton(pStrafeButton);

	// MultishotButton(7)
	CSlotButton* pMultishotButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_DEMONHUNTER_ARCHERY, SLOT_ID_DEMONHUNTER_MULTISHOT);
	m_pLayer->AddObject(pMultishotButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pMultishotButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.075f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pMultishotButton->Initialize();
	AddButton(pMultishotButton);

	// ClusterArrowButton(8)
	CSlotButton* pClusterArrowButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_DEMONHUNTER_ARCHERY, SLOT_ID_DEMONHUNTER_CLUSTER_ARROW);
	m_pLayer->AddObject(pClusterArrowButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pClusterArrowButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.075f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pClusterArrowButton->Initialize();
	AddButton(pClusterArrowButton);

	// RainOfVengeanceButton(9)
	CSlotButton* pRainOfVengeanceButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_DEMONHUNTER_ARCHERY, SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE);
	m_pLayer->AddObject(pRainOfVengeanceButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pRainOfVengeanceButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.225f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pRainOfVengeanceButton->Initialize();
	AddButton(pRainOfVengeanceButton);

	// DownArrowSign
	m_pDownArrowSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_DownArrow"));
	m_pLayer->AddObject(m_pDownArrowSign, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDownArrowSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.315f + m_iIndex * 0.07f, -0.81f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.075f, 0.12f, 0.0f);
	m_pDownArrowSign->Initialize();

	// Select
	for(int i = 6; i < 10; ++i)
	{
		SLOT_ID eSlotID = ((CSlotButton*)m_ButtonVec[i])->GetSlotID();

		if(eSlotID == m_eSlotID)
		{
			m_iSelect = i;
			break;
		}
	}

	// Renew
	Renew();
}

int CDemonHunterArcheryWindow::Update()
{
	CWindowUI::Update();

	// XButton & CancelButton
	if(m_ButtonVec[0]->IsLUp() || m_ButtonVec[2]->IsLUp())
		Destroy();

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

	// Stat
	Stat* pStat = ((CPlayer*)pPlayer)->GetStat();

	// ConfirmButton
	if(m_ButtonVec[1]->IsLUp())
	{
		switch(m_eSlotID)
		{
		case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterHungeringArrowSlot);
			break;
		case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterEntanglingShotSlot);
			break;
		case SLOT_ID_DEMONHUNTER_BOLA:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterBolaSlot);
			break;
		case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterEvasiveFireSlot);
			break;
		case SLOT_ID_DEMONHUNTER_GRENADES:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterGrenadesSlot);
			break;
		case SLOT_ID_DEMONHUNTER_IMPALE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterImpaleSlot);
			break;
		case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterRapidFireSlot);
			break;
		case SLOT_ID_DEMONHUNTER_CHAKRAM:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterChakramSlot);
			break;
		case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterElementalArrowSlot);
			break;
		case SLOT_ID_DEMONHUNTER_CALTROPS:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterCaltropsSlot);
			break;
		case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterSmokeScreenSlot);
			break;
		case SLOT_ID_DEMONHUNTER_SHADOW_POWER:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterShadowPowerSlot);
			break;
		case SLOT_ID_DEMONHUNTER_VAULT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterVaultSlot);
			break;
		case SLOT_ID_DEMONHUNTER_PREPARATION:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterPreparationSlot);
			break;
		case SLOT_ID_DEMONHUNTER_COMPANION:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterCompanionSlot);
			break;
		case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterMarkedForDeathSlot);
			break;
		case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterFanOfKnivesSlot);
			break;
		case SLOT_ID_DEMONHUNTER_SPIKE_TRAP:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterSpikeTrapSlot);
			break;
		case SLOT_ID_DEMONHUNTER_SENTRY:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterSentrySlot);
			break;
		case SLOT_ID_DEMONHUNTER_STRAFE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterStrafeSlot);
			break;
		case SLOT_ID_DEMONHUNTER_MULTISHOT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterMultishotSlot);
			break;
		case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterClusterArrowSlot);
			break;
		case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CDemonHunterRainOfVengeanceSlot);
			break;
		}

		// RenewWindow
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);

		// Destroy
		Destroy();
	}

	// LeftButton
	if(m_ButtonVec[3]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES, m_iIndex, m_eSlotID);

	// RightButton
	if(m_ButtonVec[4]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY, m_iIndex, m_eSlotID);

	// SlotButton
	if(m_ButtonVec[6]->IsLDown())
	{
		if(pStat->iLevel >= 19)
		{
			m_iSelect = 6;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[6])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[7]->IsLDown())
	{
		if(pStat->iLevel >= 22)
		{
			m_iSelect = 7;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[7])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[8]->IsLDown())
	{
		if(pStat->iLevel >= 27)
		{
			m_iSelect = 8;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[8])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[9]->IsLDown())
	{
		if(pStat->iLevel >= 30)
		{
			m_iSelect = 9;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[9])->GetSlotID();
			Renew();
		}
	}

	// SelectedSkillButton - 0
	m_ButtonVec[5]->SetState(0);

	// Select
	if(m_iSelect != -1)
		m_ButtonVec[m_iSelect]->SetState(UI_OVER);

	return 0;
}

void CDemonHunterArcheryWindow::Render()
{
	CWindowUI::Render();

	for(int i = 6; i < 10; ++i)
	{
		if(m_ButtonVec[i]->IsEnable())
		{
			CFontMgr::GetInstance()->GetBauhaus(16, 6)->DrawText(NULL, m_tszName[i - 6], -1, &m_rcName[i - 6], DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			CFontMgr::GetInstance()->GetBauhaus(16, 6)->DrawText(NULL, m_tszName[i - 6], -1, &m_rcName[i - 6], DT_CENTER, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			CFontMgr::GetInstance()->GetBauhaus(16, 6)->DrawText(NULL, m_tszLevel[i - 6], -1, &m_rcLevel[i - 6], DT_CENTER, D3DXCOLOR(0.8313f, 0.0705f, 0.0705f, 1.0f));
		}
	}
}

void CDemonHunterArcheryWindow::Release()
{
	// DownArrowSign
	if(m_pDownArrowSign != NULL)
	{
		m_pDownArrowSign->Destroy();
		m_pDownArrowSign = NULL;
	}
}

void CDemonHunterArcheryWindow::Renew()
{
	// SelectedSkillButton
	if(m_ButtonVec[5] != NULL)
	{
		m_ButtonVec[5]->Destroy();
		m_ButtonVec[5] = NULL;
	}

	m_ButtonVec[5] = new CSkillButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_END, m_eSlotID);
	m_pLayer->AddObject(m_ButtonVec[5], LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[5]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.275f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_ButtonVec[5]->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_ButtonVec[5]->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	m_ButtonVec[5]->Initialize();

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

	// Stat
	Stat* pStat = ((CPlayer*)pPlayer)->GetStat();

	// SkillButton
	if(pStat->iLevel < 19)
		m_ButtonVec[6]->Disable();
	else
		m_ButtonVec[6]->Enable();

	if(pStat->iLevel < 22)
		m_ButtonVec[7]->Disable();
	else
		m_ButtonVec[7]->Enable();

	if(pStat->iLevel < 27)
		m_ButtonVec[8]->Disable();
	else
		m_ButtonVec[8]->Enable();

	if(pStat->iLevel < 30)
		m_ButtonVec[9]->Disable();
	else
		m_ButtonVec[9]->Enable();
}