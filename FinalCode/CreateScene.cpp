#include "StdAfx.h"
#include "CreateScene.h"

CCreateScene::CCreateScene(CScene* _pScene)
: CScene(_pScene)
{
	// GenderSelect
	m_iGenderSelect = 0;

	// JobSelect
	m_iJobSelect = 0;

	// GenderButton
	ZeroMemory(&m_pGenderButton, sizeof(m_pGenderButton));

	// JobButton
	ZeroMemory(m_pJobButton, sizeof(m_pJobButton));

	// BackButton
	m_pBackButton = NULL;

	// CreateButton
	m_pCreateButton = NULL;

	// NameTextField
	m_pNameTextField = NULL;

	// WhiteCursor
	m_pWhiteCursor = NULL;
	
	// Model
	m_pModel = NULL;

	// Profile
	m_pProfileUI = NULL;
}

CCreateScene::~CCreateScene()
{
	Release();
}

void CCreateScene::Initialize()
{
	CScene::Initialize();
}

CScene* CCreateScene::Update()
{
	return CScene::Update();
}

void CCreateScene::Render()
{
	CScene::Render();
}

void CCreateScene::Release()
{
}

CScene* CCreateScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CCreateScene::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// CreateSceneBack
	CCreateSceneBack* pCreateSceneBack = new CCreateSceneBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(pCreateSceneBack);
	pCreateSceneBack->Initialize();

	// BarbarianJobButton
	m_pJobButton[0] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_BarbarianJob"), _T("Button_Over_BarbarianJob"), _T("Button_Down_BarbarianJob"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pJobButton[0]);
	pTransformCom = (CTransformCom*)m_pJobButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, 0.3f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pJobButton[0]->Initialize();

	// DemonHunterButton
	m_pJobButton[1] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_DemonHunterJob"), _T("Button_Over_DemonHunterJob"), _T("Button_Down_DemonHunterJob"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pJobButton[1]);
	pTransformCom = (CTransformCom*)m_pJobButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, 0.15f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pJobButton[1]->Initialize();

	// MonkButton
	m_pJobButton[2] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_MonkJob"), _T("Button_Over_MonkJob"), _T("Button_Down_MonkJob"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pJobButton[2]);
	pTransformCom = (CTransformCom*)m_pJobButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, 0.0f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pJobButton[2]->Initialize();

	// WitchDoctorButton
	m_pJobButton[3] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WitchDoctorJob"), _T("Button_Over_WitchDoctorJob"), _T("Button_Down_WitchDoctorJob"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pJobButton[3]);
	pTransformCom = (CTransformCom*)m_pJobButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, -0.15f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pJobButton[3]->Initialize();

	// Wizard
	m_pJobButton[4] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_WizardJob"), _T("Button_Over_WizardJob"), _T("Button_Down_WizardJob"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pJobButton[4]);
	pTransformCom = (CTransformCom*)m_pJobButton[4]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, -0.3f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pJobButton[4]->Initialize();

	// MaleButton
	m_pGenderButton[0] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Male"), _T("Button_Over_Male"), _T("Button_Down_Male"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pGenderButton[0]);
	pTransformCom = (CTransformCom*)m_pGenderButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, -0.49f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.08645f, 0.1382f, 0.0f);
	m_pGenderButton[0]->Initialize();

	// FemaleButton
	m_pGenderButton[1] = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Female"), _T("Button_Over_Female"), _T("Button_Down_Female"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pGenderButton[1]);
	pTransformCom = (CTransformCom*)m_pGenderButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.65f, -0.49f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.08645f, 0.1382f, 0.0f);
	m_pGenderButton[1]->Initialize();

	// BackButton
	m_pBackButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Back"), _T("Button_Over_Back"), _T("Button_Down_Back"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pBackButton);
	pTransformCom = (CTransformCom*)m_pBackButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, -0.75f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2644f, 0.0732f, 0.0f);
	m_pBackButton->Initialize();

	// CreateButton
	m_pCreateButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Create"), _T("Button_Over_Create"), _T("Button_Down_Create"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCreateButton);
	pTransformCom = (CTransformCom*)m_pCreateButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.75f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2644f, 0.0732f, 0.0f);
	m_pCreateButton->Initialize();

	// NameTextField
	m_pNameTextField = new CNameTextField(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pNameTextField);
	m_pNameTextField->Initialize();
	m_pNameTextField->Enable();

	// WhiteCursor
	m_pWhiteCursor = new CWhiteCursor(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pWhiteCursor);
	pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.17f, -0.625f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.002f, 0.05f, 0.0f);
	m_pWhiteCursor->Initialize();

	// Model
	m_pModel = new CModel(NULL, OBJ_TYPE_DYNAMIC, _T("Barbarian_Male_Base_Boots"), _T("Barbarian_Male_Base_Hair"), _T("Barbarian_Male_Base_Hands"), _T("Barbarian_Male_Base_Pants"), _T("Barbarian_Male_Base_Upper"));
	m_pLayer[LAYER_TYPE_MODEL]->AddObject(m_pModel);
	pTransformCom = (CTransformCom*)m_pModel->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -60.0f, 0.0f);
	m_pModel->Initialize();

	// Profile
	m_pProfileUI = new CBarbarianProfile(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pProfileUI);
	m_pProfileUI->Initialize();

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

CScene* CCreateScene::UpdatePlay()
{
	bool bChange = false;
	for(int i = 0; i < 2; ++i)
	{
		if(m_pGenderButton[i]->IsLUp() && m_iGenderSelect != i)
		{
			m_iGenderSelect = i;
			bChange = true;
			break;
		}
	}

	for(int i = 0; i < 5; ++i)
	{
		if(m_pJobButton[i]->IsLUp() && m_iJobSelect != i)
		{
			m_iJobSelect = i;
			bChange = true;
			break;
		}
	}
	
	m_pJobButton[m_iJobSelect]->AddState(UI_OVER);
	m_pGenderButton[m_iGenderSelect]->AddState(UI_OVER);

	if(bChange)
	{
		TCHAR tszBase[MIN_STR], tszBoots[MIN_STR], tszHair[MIN_STR], tszHands[MIN_STR], tszPants[MIN_STR], tszUpper[MIN_STR];

		// Job
		if(m_iJobSelect == 0)
			_tcscpy_s(tszBase, MIN_STR, _T("Barbarian_"));
		else if(m_iJobSelect == 1)
			_tcscpy_s(tszBase, MIN_STR, _T("DemonHunter_"));
		else if(m_iJobSelect == 2)
			_tcscpy_s(tszBase, MIN_STR, _T("Monk_"));
		else if(m_iJobSelect == 3)
			_tcscpy_s(tszBase, MIN_STR, _T("WitchDoctor_"));
		else if(m_iJobSelect == 4)
			_tcscpy_s(tszBase, MIN_STR, _T("Wizard_"));

		// Gender
		if(m_iGenderSelect == 0)
			_tcscat_s(tszBase, MIN_STR, _T("Male_Base_"));
		else if(m_iGenderSelect == 1)
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
		m_pModel->Destroy();
		m_pModel = new CModel(NULL, OBJ_TYPE_DYNAMIC, tszBoots, tszHair, tszHands, tszPants, tszUpper);
		m_pLayer[LAYER_TYPE_MODEL]->AddObject(m_pModel);
		pTransformCom = (CTransformCom*)m_pModel->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -60.0f, 0.0f);
		m_pModel->Initialize();

		// Profile
		m_pProfileUI->Destroy();

		if(m_iJobSelect == 0)
			m_pProfileUI = new CBarbarianProfile(NULL, OBJ_TYPE_DYNAMIC);
		else if(m_iJobSelect == 1)
			m_pProfileUI = new CDemonHunterProfile(NULL, OBJ_TYPE_DYNAMIC);
		else if(m_iJobSelect == 2)
			m_pProfileUI = new CMonkProfile(NULL, OBJ_TYPE_DYNAMIC);
		else if(m_iJobSelect == 3)
			m_pProfileUI = new CWitchDoctorProfile(NULL, OBJ_TYPE_DYNAMIC);
		else if(m_iJobSelect == 4)
			m_pProfileUI = new CWizardProfile(NULL, OBJ_TYPE_DYNAMIC);

		m_pLayer[LAYER_TYPE_UI]->AddObject(m_pProfileUI);
		m_pProfileUI->Initialize();
	}

	if(m_pBackButton->IsLUp())
		return new CSelectScene(this);

	if(m_pCreateButton->IsLUp())
	{
		int iResult = CDataMgr::GetInstance()->Create(m_pNameTextField->GetText(), m_iGenderSelect, m_iJobSelect);
		if(iResult == 0)
		{
			CDataMgr::GetInstance()->Save();
			return new CSelectScene(this);
		}
		else if(iResult == 1)
		{
			CNameEmptyMessage* pNameEmptyMessage = new CNameEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pNameEmptyMessage);
			pNameEmptyMessage->Initialize();
		}
		else if(iResult == 2)
		{
			CCharacterFullMessage* pCharacterFullMessage = new CCharacterFullMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pCharacterFullMessage);
			pCharacterFullMessage->Initialize();
		}
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.17f, -0.625f, 0.0f);
	pTransformCom->m_vPos.x = pTransformCom->m_vPos.x + m_pNameTextField->GetWidth() / float(WINCX) * 2.0f;

	return CScene::UpdatePlay();
}