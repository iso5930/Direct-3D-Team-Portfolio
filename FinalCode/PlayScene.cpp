#include "StdAfx.h"
#include "PlayScene.h"

CPlayScene::CPlayScene(CScene* _pScene)
: CScene(_pScene)
{
}

CPlayScene::~CPlayScene()
{
	Release();
}

void CPlayScene::Initialize()
{
	CScene::Initialize();
}

CScene* CPlayScene::Update()
{
	return CScene::Update();
}

void CPlayScene::Render()
{
}

void CPlayScene::Release()
{
}

CScene* CPlayScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CPlayScene::UpdateComplete()
{
	return CScene::UpdateComplete();
}

CScene* CPlayScene::UpdatePlay()
{
	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

	// Barbarian
	if(pAccount->info.iJob == 0 && pAccount->info.iGender == 0)
	{
		CBarbarian_Male* pPlayer = new CBarbarian_Male(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	else if(pAccount->info.iJob == 0 && pAccount->info.iGender == 1)
	{
		CBarbarian_Female* pPlayer = new CBarbarian_Female(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	// DemonHunter
	else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 0)
	{
		CDemonHunter_Male* pPlayer = new CDemonHunter_Male(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 1)
	{
		CDemonHunter_Female* pPlayer = new CDemonHunter_Female(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	// Monk
	else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 0)
	{
		CMonk_Male* pPlayer = new CMonk_Male(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 1)
	{
		CMonk_Female* pPlayer = new CMonk_Female(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	// WitchDoctor
	else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 0)
	{
		CWitchDoctor_Male* pPlayer = new CWitchDoctor_Male(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 1)
	{
		CWitchDoctor_Female* pPlayer = new CWitchDoctor_Female(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	// Wizard
	else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 0)
	{
		CWizard_Male* pPlayer = new CWizard_Male(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}
	else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 1)
	{
		CWizard_Female* pPlayer = new CWizard_Female(_T("Player"), OBJ_TYPE_STATIC);
		m_pLayer[LAYER_TYPE_PLAYER]->AddObject(pPlayer);
		pPlayer->Initialize();
	}

	// PlayerCamera
	CPlayerCamera* pCamera = new CPlayerCamera(_T("PlayerCamera"), OBJ_TYPE_STATIC, 0);
	m_pLayer[LAYER_TYPE_CAMERA]->AddObject(pCamera);
	pCamera->SetProj(D3DXToRadian(60.0f), float(WINCX) / float(WINCY), 1.0f, 3000.0f);
	pCamera->Initialize();
	CCameraMgr::GetInstance()->Enable(0);

	// PlayScene
	if(_tcscmp(pAccount->info.tszMapKey, _T("Tristram")) == 0)
		return new CPlayScene_Tristram(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("Cathedral_F1")) == 0)
		return new CPlayScene_Cathedral_F1(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("Cathedral_F2")) == 0)
		return new CPlayScene_Cathedral_F2(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("Cathedral_F3")) == 0)
		return new CPlayScene_Cathedral_F3(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("Cathedral_F4")) == 0)
		return new CPlayScene_Cathedral_F4(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("RoyalChamber")) == 0)
		return new CPlayScene_RoyalChamber(this);
	else if(_tcscmp(pAccount->info.tszMapKey, _T("ReorikMansion")) == 0)
		return new CPlayScene_ReorikMansion(this);

	return CScene::UpdatePlay();
}