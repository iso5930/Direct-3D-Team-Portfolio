#include "StdAfx.h"
#include "BarbarianMightWindow.h"

CBarbarianMightWindow::CBarbarianMightWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Barbarian_Might"))
{
	// Select
	m_iSelect = -1;

	// Index
	m_iIndex = _iIndex;

	// SlotID
	m_eSlotID = _eSlotID;

	// Name
	SetRect(&m_rcName[0], 494, 212, 594, 262);
	SetRect(&m_rcName[1], 590, 212, 690, 262);
	SetRect(&m_rcName[2], 686, 212, 786, 262);
	_tcscpy_s(m_tszName[0], MIN_STR, _T("제압"));
	_tcscpy_s(m_tszName[1], MIN_STR, _T("보복"));
	_tcscpy_s(m_tszName[2], MIN_STR, _T("맹렬한 돌진"));

	// Level
	SetRect(&m_rcLevel[0], 494, 127, 594, 177);
	SetRect(&m_rcLevel[1], 590, 127, 690, 177);
	SetRect(&m_rcLevel[2], 686, 127, 786, 177);
	_tcscpy_s(m_tszLevel[0], MIN_STR, _T("9"));
	_tcscpy_s(m_tszLevel[1], MIN_STR, _T("13"));
	_tcscpy_s(m_tszLevel[2], MIN_STR, _T("21"));

	// DownArrowSign
	m_pDownArrowSign = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.03f, 1.5782f, 0.0f);
}

CBarbarianMightWindow::~CBarbarianMightWindow()
{
	Release();
}

void CBarbarianMightWindow::Initialize()
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

	// OverpowerButton(6)
	CSlotButton* pOverpowerButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_MIGHT, SLOT_ID_BARBARIAN_OVERPOWER);
	m_pLayer->AddObject(pOverpowerButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pOverpowerButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pOverpowerButton->Initialize();
	AddButton(pOverpowerButton);

	// RevengeButton(7)
	CSlotButton* pRevengeButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_MIGHT, SLOT_ID_BARBARIAN_REVENGE);
	m_pLayer->AddObject(pRevengeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pRevengeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pRevengeButton->Initialize();
	AddButton(pRevengeButton);

	// FuriousChargeButton(8)
	CSlotButton* pFuriousChargeButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_BARBARIAN_MIGHT, SLOT_ID_BARBARIAN_FURIOUS_CHARGE);
	m_pLayer->AddObject(pFuriousChargeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pFuriousChargeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pFuriousChargeButton->Initialize();
	AddButton(pFuriousChargeButton);

	// DownArrowSign
	m_pDownArrowSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_DownArrow"));
	m_pLayer->AddObject(m_pDownArrowSign, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDownArrowSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.315f + m_iIndex * 0.07f, -0.81f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.075f, 0.12f, 0.0f);
	m_pDownArrowSign->Initialize();

	// Select
	for(int i = 6; i < 9; ++i)
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

int CBarbarianMightWindow::Update()
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
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE, m_iIndex, m_eSlotID);

	// RightButton
	if(m_ButtonVec[4]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_TACTICS, m_iIndex, m_eSlotID);

	// SlotButton
	if(m_ButtonVec[6]->IsLDown())
	{
		if(pStat->iLevel >= 9)
		{
			m_iSelect = 6;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[6])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[7]->IsLDown())
	{
		if(pStat->iLevel >= 13)
		{
			m_iSelect = 7;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[7])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[8]->IsLDown())
	{
		if(pStat->iLevel >= 21)
		{
			m_iSelect = 8;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[8])->GetSlotID();
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

void CBarbarianMightWindow::Render()
{
	CWindowUI::Render();

	for(int i = 6; i < 9; ++i)
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

void CBarbarianMightWindow::Release()
{
	// DownArrowSign
	if(m_pDownArrowSign != NULL)
	{
		m_pDownArrowSign->Destroy();
		m_pDownArrowSign = NULL;
	}
}

void CBarbarianMightWindow::Renew()
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
	if(pStat->iLevel < 9)
		m_ButtonVec[6]->Disable();
	else
		m_ButtonVec[6]->Enable();

	if(pStat->iLevel < 13)
		m_ButtonVec[7]->Disable();
	else
		m_ButtonVec[7]->Enable();

	if(pStat->iLevel < 21)
		m_ButtonVec[8]->Disable();
	else
		m_ButtonVec[8]->Enable();
}