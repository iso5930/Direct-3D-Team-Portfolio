#include "StdAfx.h"
#include "SelectScene.h"

CSelectScene::CSelectScene(CScene* _pScene)
: CScene(_pScene)
{
	// Select
	m_iSelect = CDataMgr::GetInstance()->GetSelect();

	// Scroll
	m_iScroll = (m_iSelect / 6) * (m_iSelect % 6);

	// MaxScroll
	m_iMaxScroll = CDataMgr::GetInstance()->GetCharacterNum() - 7;
	if(m_iMaxScroll < 0)
		m_iMaxScroll = 0;

	// CancelButton
	m_pCancelButton = NULL;

	// CharacterCreateButton
	m_pCharacterCreateButton = NULL;

	// CharacterSelectButton
	m_pCharacterSelectButton = NULL;

	// CharacterDeleteButton
	m_pCharacterDeleteButton = NULL;

	// CharacterButton
	ZeroMemory(m_pCharacterButton, sizeof(m_pCharacterButton));

	// ScrollUpButton
	m_pScrollUpButton = NULL;

	// ScrollDownButton
	m_pScrollDownButton = NULL;

	// VScroll
	m_pVScroll = NULL;

	// Model
	m_pModel = NULL;

	// BadgeUI
	m_pBadgeUI = NULL;
}

CSelectScene::~CSelectScene()
{
	Release();
}

void CSelectScene::Initialize()
{
	CScene::Initialize();
}

CScene* CSelectScene::Update()
{
	return CScene::Update();
}

void CSelectScene::Render()
{
	CScene::Render();
}

void CSelectScene::Release()
{
}

CScene* CSelectScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CSelectScene::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// SelectSceneBack
	CSelectSceneBack* pSelectSceneBack = new CSelectSceneBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(pSelectSceneBack);
	pSelectSceneBack->Initialize();

	// CancelButton
	m_pCancelButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Cancel"), _T("Button_Over_Cancel"), _T("Button_Down_Cancel"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCancelButton);
	pTransformCom = (CTransformCom*)m_pCancelButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.73f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pCancelButton->Initialize();

	// CharacterCreateButton
	m_pCharacterCreateButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_CharacterCreate"), _T("Button_Over_CharacterCreate"), _T("Button_Down_CharacterCreate"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCharacterCreateButton);
	pTransformCom = (CTransformCom*)m_pCharacterCreateButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.73f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pCharacterCreateButton->Initialize();

	// CharacterSelectButton
	m_pCharacterSelectButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_CharacterSelect"), _T("Button_Over_CharacterSelect"), _T("Button_Down_CharacterSelect"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCharacterSelectButton);
	pTransformCom = (CTransformCom*)m_pCharacterSelectButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pCharacterSelectButton->Initialize();

	// CharacterDeleteButton
	m_pCharacterDeleteButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_CharacterDelete"), _T("Button_Over_CharacterDelete"), _T("Button_Down_CharacterDelete"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCharacterDeleteButton);
	pTransformCom = (CTransformCom*)m_pCharacterDeleteButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.73f, -0.675f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pCharacterDeleteButton->Initialize();

	// ScrollUpButton
	m_pScrollUpButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Up"), _T("Button_Over_Up"), _T("Button_Down_Up"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pScrollUpButton);
	pTransformCom = (CTransformCom*)m_pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.543f, 0.37f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03958f, 0.0616f, 0.0f);
	m_pScrollUpButton->Initialize();

	// ScrollDownButton
	m_pScrollDownButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Down"), _T("Button_Over_Down"), _T("Button_Down_Down"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pScrollDownButton);
	pTransformCom = (CTransformCom*)m_pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.543f, -0.69f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03958f, 0.0616f, 0.0f);
	m_pScrollDownButton->Initialize();

	// VScroll
	m_pVScroll = new CVScroll(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pVScroll);
	pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos.x = -0.543f;
	pTransformCom->m_vSize.x = 0.02958f;
	m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.3325f, -0.65325f);
	m_pVScroll->Initialize();

	// RenewButton
	RenewButton();

	// RenewModel
	RenewModelAndBadge();

	// UpdateButton
	UpdateButton();

	// UpdateScroll
	UpdateScroll();

	// Camera0
	CCamera* pCamera0 = new CCamera(NULL, OBJ_TYPE_DYNAMIC, 0);
	m_pLayer[LAYER_TYPE_CAMERA]->AddObject(pCamera0);
	pCamera0->SetView(&D3DXVECTOR3(0.0f, 0.0f, -200.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera0->SetProj(D3DXToRadian(60.0f), float(WINCX) / float(WINCY), 1.0f, 3000.0f);
	pCamera0->Initialize();

	// Light1
	CLight* pLight1 = new CLight(NULL, OBJ_TYPE_DYNAMIC, 1, LIGHT_TYPE_DIRECTION, &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), &D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f), NULL, &D3DXVECTOR4(0.0f, -1.0f, 1.0f, 0.0f), 0.0f);
	m_pLayer[LAYER_TYPE_LIGHT]->AddObject(pLight1);
	pLight1->Initialize();

	CCameraMgr::GetInstance()->Enable(0);

	return CScene::UpdateComplete();
}

CScene* CSelectScene::UpdatePlay()
{
	if(m_pCancelButton->IsLUp())
		return new CLobbyScene(this);

	if(m_pCharacterCreateButton->IsLUp())
	{
		if(CDataMgr::GetInstance()->GetCharacterNum() >= 10)
		{
			CCharacterFullMessage* pCharacterFullMessage = new CCharacterFullMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pCharacterFullMessage);
			pCharacterFullMessage->Initialize();
		}
		else
			return new CCreateScene(this);
	}

	if(m_pCharacterSelectButton->IsLUp())
	{
		if(m_iSelect >= CDataMgr::GetInstance()->GetCharacterNum())
		{
			CCharacterEmptyMessage* pCharacterEmptyMessage = new CCharacterEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pCharacterEmptyMessage);
			pCharacterEmptyMessage->Initialize();
		}
		else
		{
			CDataMgr::GetInstance()->SetSelect(m_iSelect);
			CDataMgr::GetInstance()->Save();
			return new CLobbyScene(this);
		}
	}

	if(m_pCharacterDeleteButton->IsLUp())
	{
		if(m_iSelect >= CDataMgr::GetInstance()->GetCharacterNum())
		{
			CCharacterEmptyMessage* pCharacterEmptyMessage = new CCharacterEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pCharacterEmptyMessage);
			pCharacterEmptyMessage->Initialize();
		}
		else
		{
			CDataMgr::GetInstance()->Delete(m_iSelect);
			CDataMgr::GetInstance()->Save();

			// Select
			if(m_iSelect >= CDataMgr::GetInstance()->GetCharacterNum())
			{
				if(--m_iSelect < 0)
					m_iSelect = 0;
			}

			// MaxScroll
			m_iMaxScroll = CDataMgr::GetInstance()->GetCharacterNum() - 7;
			if(m_iMaxScroll < 0)
				m_iMaxScroll = 0;

			if(m_iScroll > m_iMaxScroll)
				m_iScroll = m_iMaxScroll;

			// RenewButton
			RenewButton();

			// RenewModel
			RenewModelAndBadge();

			// UpdateButton
			UpdateButton();

			// UpdateScroll
			UpdateScroll();

			// ScrollSetup
			m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.3325f, -0.65325f);
		}
	}

	for(int i = 0; i < 10; ++i)
	{
		if(m_pCharacterButton[i] == NULL)
			break;

		if(m_pCharacterButton[i]->IsLUp() && m_iSelect != i)
		{
			m_iSelect = i;
			RenewModelAndBadge();
			break;
		}
	}

	if(m_pScrollUpButton->IsLUp())
	{
		if(--m_iScroll < 0)
			m_iScroll = 0;

		m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.3325f, -0.65325f);
		UpdateButton();
	}
	else if(m_pScrollDownButton->IsLUp())
	{
		if(++m_iScroll > m_iMaxScroll)
			m_iScroll = m_iMaxScroll;

		m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.3325f, -0.65325f);
		UpdateButton();
	}

	if(m_iScroll != m_pVScroll->GetScroll())
	{
		m_iScroll = m_pVScroll->GetScroll();
		UpdateButton();
	}

	if(m_pCharacterButton[m_iSelect] != NULL)
		m_pCharacterButton[m_iSelect]->AddState(UI_OVER);

	return CScene::UpdatePlay();
}

void CSelectScene::RenewButton()
{
	for(int i = 0; i < 10; ++i)
	{
		if(m_pCharacterButton[i] == NULL)
			break;

		m_pCharacterButton[i]->Destroy();
		m_pCharacterButton[i] = NULL;
	}

	for(int i = 0; i < 10; ++i)
	{
		Account* pAccount = CDataMgr::GetInstance()->GetAccount(i);
		if(pAccount == NULL)
			break;

		if(pAccount->info.iGender == 0)
		{
			if(pAccount->info.iJob == 0)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_BarbarianMale"), _T("Button_Over_BarbarianMale"), _T("Button_Down_BarbarianMale"));
			else if(pAccount->info.iJob == 1)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_DemonHunterMale"), _T("Button_Over_DemonHunterMale"), _T("Button_Down_DemonHunterMale"));
			else if(pAccount->info.iJob == 2)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_MonkMale"), _T("Button_Over_MonkMale"), _T("Button_Down_MonkMale"));
			else if(pAccount->info.iJob == 3)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WitchDoctorMale"), _T("Button_Over_WitchDoctorMale"), _T("Button_Down_WitchDoctorMale"));
			else if(pAccount->info.iJob == 4)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WizardMale"), _T("Button_Over_WizardMale"), _T("Button_Down_WizardMale"));
		}
		else if(pAccount->info.iGender == 1)
		{
			if(pAccount->info.iJob == 0)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_BarbarianFemale"), _T("Button_Over_BarbarianFemale"), _T("Button_Down_BarbarianFemale"));
			else if(pAccount->info.iJob == 1)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_DemonHunterFemale"), _T("Button_Over_DemonHunterFemale"), _T("Button_Down_DemonHunterFemale"));
			else if(pAccount->info.iJob == 2)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_MonkFemale"), _T("Button_Over_MonkFemale"), _T("Button_Down_MonkFemale"));
			else if(pAccount->info.iJob == 3)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WitchDoctorFemale"), _T("Button_Over_WitchDoctorFemale"), _T("Button_Down_WitchDoctorFemale"));
			else if(pAccount->info.iJob == 4)
				m_pCharacterButton[i] = new CCharacterButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WizardFemale"), _T("Button_Over_WizardFemale"), _T("Button_Down_WizardFemale"));
		}

		m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCharacterButton[i]);
		m_pCharacterButton[i]->Setup(pAccount->info.tszName, pAccount->stat.iLevel, pAccount->info.iJob);
		m_pCharacterButton[i]->Initialize();
	}
}

void CSelectScene::RenewModelAndBadge()
{
	if(m_pModel != NULL)
	{
		m_pModel->Destroy();
		m_pModel = NULL;
	}

	if(m_pBadgeUI != NULL)
	{
		m_pBadgeUI->Destroy();
		m_pBadgeUI = NULL;
	}

	// Model
	if(CDataMgr::GetInstance()->GetAccount(m_iSelect) != NULL)
	{
		Account* pAccount = CDataMgr::GetInstance()->GetAccount(m_iSelect);
		TCHAR tszBase[MIN_STR], tszBoots[MIN_STR], tszHair[MIN_STR], tszHands[MIN_STR], tszPants[MIN_STR], tszUpper[MIN_STR];

		// Job
		if(pAccount->info.iJob == 0)
			_tcscpy_s(tszBase, MIN_STR, _T("Barbarian_"));
		else if(pAccount->info.iJob == 1)
			_tcscpy_s(tszBase, MIN_STR, _T("DemonHunter_"));
		else if(pAccount->info.iJob == 2)
			_tcscpy_s(tszBase, MIN_STR, _T("Monk_"));
		else if(pAccount->info.iJob == 3)
			_tcscpy_s(tszBase, MIN_STR, _T("WitchDoctor_"));
		else if(pAccount->info.iJob == 4)
			_tcscpy_s(tszBase, MIN_STR, _T("Wizard_"));

		// Gender
		if(pAccount->info.iGender == 0)
			_tcscat_s(tszBase, MIN_STR, _T("Male_Base_"));
		else if(pAccount->info.iGender == 1)
			_tcscat_s(tszBase, MIN_STR, _T("Female_Base_"));

		// Boots
		_tcscpy_s(tszBoots, MIN_STR, tszBase);
		_tcscat_s(tszBoots, MIN_STR, _T("Boots"));
		// Hair
		_tcscpy_s(tszHair, MIN_STR, tszBase);
		_tcscat_s(tszHair, MIN_STR, _T("Hair"));
		// Hands
		_tcscpy_s(tszHands, MIN_STR, tszBase);
		_tcscat_s(tszHands, MIN_STR, _T("Hands"));
		// Pants
		_tcscpy_s(tszPants, MIN_STR, tszBase);
		_tcscat_s(tszPants, MIN_STR, _T("Pants"));
		// Upper
		_tcscpy_s(tszUpper, MIN_STR, tszBase);
		_tcscat_s(tszUpper, MIN_STR, _T("Upper"));

		// TransformCom
		CTransformCom* pTransformCom;

		// Model
		m_pModel = new CModel(NULL, OBJ_TYPE_DYNAMIC, tszBoots, tszHair, tszHands, tszPants, tszUpper);
		m_pLayer[LAYER_TYPE_MODEL]->AddObject(m_pModel);
		pTransformCom = (CTransformCom*)m_pModel->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -60.0f, 0.0f);
		m_pModel->Initialize();

		// BadgeUI
		if(pAccount->info.iJob == 0)
		{
			if(pAccount->info.iGender == 0)
				m_pBadgeUI = new CBarbarianMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				m_pBadgeUI = new CBarbarianFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 1)
		{
			if(pAccount->info.iGender == 0)
				m_pBadgeUI = new CDemonHunterMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				m_pBadgeUI = new CDemonHunterFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 2)
		{
			if(pAccount->info.iGender == 0)
				m_pBadgeUI = new CMonkMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				m_pBadgeUI = new CMonkFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 3)
		{
			if(pAccount->info.iGender == 0)
				m_pBadgeUI = new CWitchDoctorMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				m_pBadgeUI = new CWitchDoctorFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 4)
		{
			if(pAccount->info.iGender == 0)
				m_pBadgeUI = new CWizardMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				m_pBadgeUI = new CWizardFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}

		m_pLayer[LAYER_TYPE_UI]->AddObject(m_pBadgeUI);
		m_pBadgeUI->Initialize();
	}
}

void CSelectScene::UpdateButton()
{
	for(int i = 0; i < 10; ++i)
	{
		if(m_pCharacterButton[i] == NULL)
			break;

		CTransformCom* pTransformCom = (CTransformCom*)m_pCharacterButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for(int i = m_iScroll; i < m_iScroll + 7 && i < 10; ++i)
	{
		if(m_pCharacterButton[i] == NULL)
			break;

		CTransformCom* pTransformCom;
		pTransformCom = (CTransformCom*)m_pCharacterButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.74f, 0.33f - 0.163f * (i - m_iScroll), 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.345f, 0.13f, 0.0f);
	}
}

void CSelectScene::UpdateScroll()
{
	if(m_iMaxScroll > 0)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03958f, 0.0616f, 0.0f);

		pTransformCom = (CTransformCom*)m_pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03958f, 0.0616f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.02958f;
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.0f;
	}
}