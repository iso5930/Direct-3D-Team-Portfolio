#include "StdAfx.h"
#include "WizardMasteryWindow.h"

CWizardMasteryWindow::CWizardMasteryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Wizard_Mastery"))
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
	_tcscpy_s(m_tszName[0], MIN_STR, _T("������ ����"));
	_tcscpy_s(m_tszName[1], MIN_STR, _T("�н�"));
	_tcscpy_s(m_tszName[2], MIN_STR, _T("����"));

	// Level
	SetRect(&m_rcLevel[0], 494, 127, 594, 177);
	SetRect(&m_rcLevel[1], 590, 127, 690, 177);
	SetRect(&m_rcLevel[2], 686, 127, 786, 177);
	_tcscpy_s(m_tszLevel[0], MIN_STR, _T("19"));
	_tcscpy_s(m_tszLevel[1], MIN_STR, _T("25"));
	_tcscpy_s(m_tszLevel[2], MIN_STR, _T("30"));

	// DownArrowSign
	m_pDownArrowSign = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.03f, 1.5782f, 0.0f);
}

CWizardMasteryWindow::~CWizardMasteryWindow()
{
	Release();
}

void CWizardMasteryWindow::Initialize()
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

	// ExplosiveBlastButton(6)
	CSlotButton* pExplosiveBlastButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_WIZARD_MASTERY, SLOT_ID_WIZARD_EXPLOSIVE_BLAST);
	m_pLayer->AddObject(pExplosiveBlastButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pExplosiveBlastButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pExplosiveBlastButton->Initialize();
	AddButton(pExplosiveBlastButton);

	// MirrorImageButton(7)
	CSlotButton* pMirrorImageButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_WIZARD_MASTERY, SLOT_ID_WIZARD_MIRROR_IMAGE);
	m_pLayer->AddObject(pMirrorImageButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pMirrorImageButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pMirrorImageButton->Initialize();
	AddButton(pMirrorImageButton);

	// ArchonButton(8)
	CSlotButton* pArchonButton = new CSlotButton(NULL, OBJ_TYPE_STATIC, SLOT_TYPE_WIZARD_MASTERY, SLOT_ID_WIZARD_ARCHON);
	m_pLayer->AddObject(pArchonButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pArchonButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.15f, 0.508f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.078f, 0.159f, 0.0f);
	pArchonButton->Initialize();
	AddButton(pArchonButton);

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

int CWizardMasteryWindow::Update()
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
		CObject* pPlayer = NULL;
		m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

		switch(m_eSlotID)
		{
		case SLOT_ID_WIZARD_MAGIC_MISSILE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardMagicMissileSlot);
			break;
		case SLOT_ID_WIZARD_SHOCK_PULSE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardShockPulseSlot);
			break;
		case SLOT_ID_WIZARD_SPECTRAL_BLADE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardSpectralBladeSlot);
			break;
		case SLOT_ID_WIZARD_ELECTROCUTE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardElectrocuteSlot);
			break;
		case SLOT_ID_WIZARD_RAY_OF_FROST:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardRayOfFrostSlot);
			break;
		case SLOT_ID_WIZARD_ARCANE_ORB:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardArcaneOrbSlot);
			break;
		case SLOT_ID_WIZARD_ARCANE_TORRENT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardArcaneTorrentSlot);
			break;
		case SLOT_ID_WIZARD_DISINTEGRATE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardDisintegrateSlot);
			break;
		case SLOT_ID_WIZARD_FROST_NOVA:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardFrostNovaSlot);
			break;
		case SLOT_ID_WIZARD_DIAMOND_SKIN:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardDiamondSkinSlot);
			break;
		case SLOT_ID_WIZARD_SLOW_TIME:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardSlowTimeSlot);
			break;
		case SLOT_ID_WIZARD_TELEPORT:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardTeleportSlot);
			break;
		case SLOT_ID_WIZARD_WAVE_OF_FORCE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardWaveOfForceSlot);
			break;
		case SLOT_ID_WIZARD_ENERGY_TWISTER:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardEnergyTwisterSlot);
			break;
		case SLOT_ID_WIZARD_HYDRA:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardHydraSlot);
			break;
		case SLOT_ID_WIZARD_METEOR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardMeteorSlot);
			break;
		case SLOT_ID_WIZARD_BLIZZARD:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardBlizzardSlot);
			break;
		case SLOT_ID_WIZARD_ICE_ARMOR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardIceArmorSlot);
			break;
		case SLOT_ID_WIZARD_STORM_ARMOR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardStormArmorSlot);
			break;
		case SLOT_ID_WIZARD_MAGIC_WEAPON:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardMagicWeaponSlot);
			break;
		case SLOT_ID_WIZARD_FAMILIAR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardFamiliarSlot);
			break;
		case SLOT_ID_WIZARD_ENERGY_ARMOR:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardEnergyArmorSlot);
			break;
		case SLOT_ID_WIZARD_EXPLOSIVE_BLAST:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardExplosiveBlastSlot);
			break;
		case SLOT_ID_WIZARD_MIRROR_IMAGE:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardMirrorImageSlot);
			break;
		case SLOT_ID_WIZARD_ARCHON:
			((CPlayer*)pPlayer)->SetSlot(m_iIndex, new CWizardArchonSlot);
			break;
		}

		// RenewWindow
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);

		// Destroy
		Destroy();
	}

	// LeftButton
	if(m_ButtonVec[3]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_CONJURATION, m_iIndex, m_eSlotID);

	// RightButton
	if(m_ButtonVec[4]->IsLUp())
		CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_PRIMARY, m_iIndex, m_eSlotID);
	
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
		if(pStat->iLevel >= 25)
		{
			m_iSelect = 7;
			m_eSlotID = ((CSlotButton*)m_ButtonVec[7])->GetSlotID();
			Renew();
		}
	}
	else if(m_ButtonVec[8]->IsLDown())
	{
		if(pStat->iLevel >= 30)
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

void CWizardMasteryWindow::Render()
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

void CWizardMasteryWindow::Release()
{
	// DownArrowSign
	if(m_pDownArrowSign != NULL)
	{
		m_pDownArrowSign->Destroy();
		m_pDownArrowSign = NULL;
	}
}

void CWizardMasteryWindow::Renew()
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
	if(pStat->iLevel < 19)
		m_ButtonVec[6]->Disable();
	else
		m_ButtonVec[6]->Enable();

	if(pStat->iLevel < 25)
		m_ButtonVec[7]->Disable();
	else
		m_ButtonVec[7]->Enable();

	if(pStat->iLevel < 30)
		m_ButtonVec[8]->Disable();
	else
		m_ButtonVec[8]->Enable();
}