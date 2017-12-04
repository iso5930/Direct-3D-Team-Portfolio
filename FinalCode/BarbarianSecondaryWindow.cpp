#include "StdAfx.h"
#include "BarbarianSecondaryWindow.h"

CBarbarianSecondaryWindow::CBarbarianSecondaryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Barbarian_Secondary"))
{
	// Select
	m_iSelect = -1;

	// Index
	m_iIndex = _iIndex;

	// SlotID
	m_eSlotID = _eSlotID;

	// Name
	SetRect(&m_rcName[0], 398, 212, 498, 262);
	SetRect(&m_rcName[1], 494, 212, 594, 262);
	SetRect(&m_rcName[2], 590, 212, 690, 262);
	SetRect(&m_rcName[3], 686, 212, 786, 262);
	SetRect(&m_rcName[4], 782, 212, 882, 262);
	_tcscpy_s(m_tszName[0], MIN_STR, _T("������ ��ġ"));
	_tcscpy_s(m_tszName[1], MIN_STR, _T("�м�"));
	_tcscpy_s(m_tszName[2], MIN_STR, _T("���� ��Ÿ"));
	_tcscpy_s(m_tszName[3], MIN_STR, _T("�ҿ뵹��"));
	_tcscpy_s(m_tszName[4], MIN_STR, _T("����� �ۻ�"));

	// Level
	SetRect(&m_rcLevel[0], 398, 127, 498, 177);
	SetRect(&m_rcLevel[1], 494, 127, 594, 177);
	SetRect(&m_rcLevel[2], 590, 127, 690, 177);
	SetRect(&m_rcLevel[3], 686, 127, 786, 177);
	SetRect(&m_rcLevel[4], 782, 127, 882, 177);
	_tcscpy_s(m_tszLevel[0], MIN_STR, _T("2"));
	_tcscpy_s(m_tszLevel[1], MIN_STR, _T("5"));
	_tcscpy_s(m_tszLevel[2], MIN_STR, _T("12"));
	_tcscpy_s(m_tszLevel[3], MIN_STR, _T("20"));
	_tcscpy_s(m_tszLevel[4], MIN_STR, _T("26"));

	// DownArrowSign
	m_pDownArrowSign = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.03f, 1.5782f, 0.0f);
}

CBarbarianSecondaryWindow::~CBarbarianSecondaryWindow()
{
	Release();
}

void CBarbarianSecondaryWindow::Initialize()
{
	CWindowUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

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

	// HammerOfTheAncientsButton(6)
	CSlotButton* pHammerOfTheAncientsButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_SECONDARY, SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS);
	m_pLayer->AddObject(pHammerOfTheAncientsButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pHammerOfTheAncientsButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.3f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pHammerOfTheAncientsButton->Initialize();
	AddButton(pHammerOfTheAncientsButton);

	// RendButton(7)
	CSlotButton* pRendButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_SECONDARY, SLOT_ID_BARBARIAN_REND);
	m_pLayer->AddObject(pRendButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pRendButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pRendButton->Initialize();
	AddButton(pRendButton);

	// SeismicSlamButton(8)
	CSlotButton* pSeismicSlamButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_SECONDARY, SLOT_ID_BARBARIAN_SEISMIC_SLAM);
	m_pLayer->AddObject(pSeismicSlamButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pSeismicSlamButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pSeismicSlamButton->Initialize();
	AddButton(pSeismicSlamButton);

	// WhirlwindButton(9)
	CSlotButton* pWhirlwindButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_SECONDARY, SLOT_ID_BARBARIAN_WHIRLWIND);
	m_pLayer->AddObject(pWhirlwindButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pWhirlwindButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pWhirlwindButton->Initialize();
	AddButton(pWhirlwindButton);

	// AncientSpearButton(10)
	CSlotButton* pAncientSpearButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_SECONDARY, SLOT_ID_BARBARIAN_ANCIENT_SPEAR);
	m_pLayer->AddObject(pAncientSpearButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pAncientSpearButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.3f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pAncientSpearButton->Initialize();
	AddButton(pAncientSpearButton);

	// DownArrowSign
	m_pDownArrowSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_DownArrow"));
	m_pLayer->AddObject(m_pDownArrowSign, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDownArrowSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.315f + m_iIndex * 0.07f, -0.81f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.075f, 0.12f, 0.0f);
	m_pDownArrowSign->Initialize();

	// Select
	for(int i = 6; i < 11; ++i)
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

int CBarbarianSecondaryWindow::Update()
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
		case SLOT_ID_BARBARIAN_BASH:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianBashSlot);
			break;
		case SLOT_ID_BARBARIAN_CLEAVE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianCleaveSlot);
			break;
		case SLOT_ID_BARBARIAN_FRENZY:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianFrenzySlot);
			break;
		case SLOT_ID_BARBARIAN_WEAPON_THROW:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianWeaponThrowSlot);
			break;
		case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianHammerOfTheAncientsSlot);
			break;
		case SLOT_ID_BARBARIAN_REND:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianRendSlot);
			break;
		case SLOT_ID_BARBARIAN_SEISMIC_SLAM:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianSeismicSlamSlot);
			break;
		case SLOT_ID_BARBARIAN_WHIRLWIND:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianWhirlwindSlot);
			break;
		case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianAncientSpearSlot);
			break;
		case SLOT_ID_BARBARIAN_GROUND_STOMP:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianGroundStompSlot);
			break;
		case SLOT_ID_BARBARIAN_LEAP:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianLeapSlot);
			break;
		case SLOT_ID_BARBARIAN_SPRINT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianSprintSlot);
			break;
		case SLOT_ID_BARBARIAN_IGNORE_PAIN:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianIgnorePainSlot);
			break;
		case SLOT_ID_BARBARIAN_OVERPOWER:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianOverpowerSlot);
			break;
		case SLOT_ID_BARBARIAN_REVENGE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianRevengeSlot);
			break;
		case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianFuriousChargeSlot);
			break;
		case SLOT_ID_BARBARIAN_THREATENING_SHOUT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianThreateningShoutSlot);
			break;
		case SLOT_ID_BARBARIAN_BATTLE_RAGE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianBattleRageSlot);
			break;
		case SLOT_ID_BARBARIAN_WAR_CRY:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianWarCrySlot);
			break;
		case SLOT_ID_BARBARIAN_EARTHQUAKE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianEarthquakeSlot);
			break;
		case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianCallOfTheAncientsSlot);
			break;
		case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CBarbarianWrathOfTheBerserkerSlot);
			break;
		}

		// RenewWindow
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);

		// Destroy
		Destroy();
	}

	// LeftButton
	if(m_ButtonVec[3]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_PRIMARY, m_iIndex, m_eSlotID);

	// RightButton
	if(m_ButtonVec[4]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE, m_iIndex, m_eSlotID);

	// SlotButton
	if(m_ButtonVec[6]->IsLDown())
	{
		if(pStat->iLevel >= 1)
		{
			m_iSelect = 6;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[6])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[7]->IsLDown())
	{
		if(pStat->iLevel >= 5)
		{
			m_iSelect = 7;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[7])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[8]->IsLDown())
	{
		if(pStat->iLevel >= 12)
		{
			m_iSelect = 8;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[8])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[9]->IsLDown())
	{
		if(pStat->iLevel >= 20)
		{
			m_iSelect = 9;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[9])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[10]->IsLDown())
	{
		if(pStat->iLevel >= 26)
		{
			m_iSelect = 10;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[10])->GetSlotID();
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

void CBarbarianSecondaryWindow::Render()
{
	CWindowUI::Render();

	for(int i = 6; i < 11; ++i)
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

void CBarbarianSecondaryWindow::Release()
{
	// DownArrowSign
	if(m_pDownArrowSign != NULL)
	{
		m_pDownArrowSign->Destroy();
		m_pDownArrowSign = NULL;
	}
}

void CBarbarianSecondaryWindow::Renew()
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

	// SlotButton
	if(pStat->iLevel < 1)
		m_ButtonVec[6]->Disable();
	else
		m_ButtonVec[6]->Enable();

	if(pStat->iLevel < 5)
		m_ButtonVec[7]->Disable();
	else
		m_ButtonVec[7]->Enable();

	if(pStat->iLevel < 12)
		m_ButtonVec[8]->Disable();
	else
		m_ButtonVec[8]->Enable();

	if(pStat->iLevel < 20)
		m_ButtonVec[9]->Disable();
	else
		m_ButtonVec[9]->Enable();

	if(pStat->iLevel < 26)
		m_ButtonVec[10]->Disable();
	else
		m_ButtonVec[10]->Enable();
}