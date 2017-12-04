#include "StdAfx.h"
#include "LobbyScene.h"

CLobbyScene::CLobbyScene(CScene* _pScene)
: CScene(_pScene)
{
	// BackButton
	m_pBackButton = NULL;

	// SettingButton
	m_pSettingButton = NULL;

	// GameContinueButton
	m_pGameContinueButton = NULL;

	// CharacterChangeButton
	m_pCharacterChangeButton = NULL;

	// Model
	m_pModel = NULL;
}

CLobbyScene::~CLobbyScene()
{
	Release();
}

void CLobbyScene::Initialize()
{
	CScene::Initialize();
}

CScene* CLobbyScene::Update()
{
	return CScene::Update();
}

void CLobbyScene::Render()
{
	CScene::Render();
}

void CLobbyScene::Release()
{
}

CScene* CLobbyScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CLobbyScene::UpdateComplete()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// LobbySceneBack
	CLobbySceneBack* pLobbySceneBack = new CLobbySceneBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(pLobbySceneBack);
	pLobbySceneBack->Initialize();

	// BackButton
	m_pBackButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Back"), _T("Button_Over_Back"), _T("Button_Down_Back"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pBackButton);
	pTransformCom = (CTransformCom*)m_pBackButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.7f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pBackButton->Initialize();

	// SettingButton
	m_pSettingButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Setting"), _T("Button_Over_Setting"), _T("Button_Down_Setting"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pSettingButton);
	pTransformCom = (CTransformCom*)m_pSettingButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, -0.675f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pSettingButton->Initialize();

	// GameContinueButton
	m_pGameContinueButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_GameContinue"), _T("Button_Over_GameContinue"), _T("Button_Down_GameContinue"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pGameContinueButton);
	pTransformCom = (CTransformCom*)m_pGameContinueButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.7f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pGameContinueButton->Initialize();

	// CharacterChangeButton
	m_pCharacterChangeButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_CharacterChange"), _T("Button_Over_CharacterChange"), _T("Button_Down_CharacterChange"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pCharacterChangeButton);
	pTransformCom = (CTransformCom*)m_pCharacterChangeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.825f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3666f, 0.1258f, 0.0f);
	m_pCharacterChangeButton->Initialize();

	// Model
	if(CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect()) != NULL)
	{
		Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());
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

		// Badge
		CBadgeUI* pBadgeUI;

		if(pAccount->info.iJob == 0)
		{
			if(pAccount->info.iGender == 0)
				pBadgeUI = new CBarbarianMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				pBadgeUI = new CBarbarianFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 1)
		{
			if(pAccount->info.iGender == 0)
				pBadgeUI = new CDemonHunterMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				pBadgeUI = new CDemonHunterFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 2)
		{
			if(pAccount->info.iGender == 0)
				pBadgeUI = new CMonkMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				pBadgeUI = new CMonkFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 3)
		{
			if(pAccount->info.iGender == 0)
				pBadgeUI = new CWitchDoctorMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				pBadgeUI = new CWitchDoctorFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}
		else if(pAccount->info.iJob == 4)
		{
			if(pAccount->info.iGender == 0)
				pBadgeUI = new CWizardMaleBadge(NULL, OBJ_TYPE_DYNAMIC);
			else
				pBadgeUI = new CWizardFemaleBadge(NULL, OBJ_TYPE_DYNAMIC);
		}

		m_pLayer[LAYER_TYPE_UI]->AddObject(pBadgeUI);
		pBadgeUI->Initialize();
	}

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

CScene* CLobbyScene::UpdatePlay()
{
	if(m_pBackButton->IsLUp())
	{
		CDataMgr::GetInstance()->Save();
		CDataMgr::GetInstance()->Reset();
		
		CLoadScene* pLoadScene = new CLoadScene(NULL, true);
		pLoadScene->SetNextScene(new CLoginScene(this));
		pLoadScene->AddUnloadVec(UNLOAD_TYPE_LOBBY_SCENE);

		return pLoadScene;
		//return new CLoginScene(this);
	}

	if(m_pSettingButton->IsLUp())
	{
		cout << "SettingButton LUp" << endl;
	}

	if(m_pGameContinueButton->IsLUp())
	{
		if(m_pModel == NULL)
		{
			CCharacterEmptyMessage* pCharacterEmptyMessage = new CCharacterEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pCharacterEmptyMessage);
			pCharacterEmptyMessage->Initialize();
		}
		else
		{
			// Account
			Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

			CLoadScene* pLoadScene = new CLoadScene(NULL, true);
			pLoadScene->SetNextScene(new CPlayScene(this));
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_TITLE_SCENE);
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_LOBBY_SCENE);
			pLoadScene->AddLoadVec(LOAD_TYPE_PLAY_SCENE);

			if(pAccount->info.iJob == 0 && pAccount->info.iGender == 0)
				pLoadScene->AddLoadVec(LOAD_TYPE_BARBARIAN_MALE);
			else if(pAccount->info.iJob == 0 && pAccount->info.iGender == 1)
				pLoadScene->AddLoadVec(LOAD_TYPE_BARBARIAN_FEMALE);
			else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 0)
				pLoadScene->AddLoadVec(LOAD_TYPE_DEMONHUNTER_MALE);
			else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 1)
				pLoadScene->AddLoadVec(LOAD_TYPE_DEMONHUNTER_FEMALE);
			else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 0)
				pLoadScene->AddLoadVec(LOAD_TYPE_MONK_MALE);
			else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 1)
				pLoadScene->AddLoadVec(LOAD_TYPE_MONK_FEMALE);
			else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 0)
				pLoadScene->AddLoadVec(LOAD_TYPE_WITCHDOCTOR_MALE);
			else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 1)
				pLoadScene->AddLoadVec(LOAD_TYPE_WITCHDOCTOR_FEMALE);
			else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 0)
				pLoadScene->AddLoadVec(LOAD_TYPE_WIZARD_MALE);
			else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 1)
				pLoadScene->AddLoadVec(LOAD_TYPE_WIZARD_FEMALE);

			return pLoadScene;
		}
	}

	if(m_pCharacterChangeButton->IsLUp())
		return new CSelectScene(this);

	return CScene::UpdatePlay();
}