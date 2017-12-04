#include "StdAfx.h"
#include "LoadScene.h"

CLoadScene::CLoadScene(CScene* _pScene, bool _bLoadBack)
: CScene(_pScene)
{
	// LoadBack
	m_bLoadBack = _bLoadBack;

	// NextScene
	m_pNextScene = NULL;
}

CLoadScene::~CLoadScene()
{
	Release();
}

void CLoadScene::Initialize()
{
	if(m_bLoadBack)
	{
		// LoadBack
		m_pLoadBack = new CLoadBack(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer[LAYER_TYPE_BACK]->AddObject(m_pLoadBack);
		m_pLoadBack->Initialize();
	}

	CScene::Initialize();
}
CScene* CLoadScene::Update()
{
	return CScene::Update();
}
void CLoadScene::Render()
{
	CScene::Render();
}
void CLoadScene::Release()
{
}

CScene* CLoadScene::UpdateLoad()
{
	// UnloadVec
	for(size_t i = 0; i < m_UnloadVec.size(); ++i)
	{
		if(m_UnloadVec[i] == UNLOAD_TYPE_BASE)
			CLoadMgr::GetInstance()->UnloadForBase();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_TITLE_SCENE)
			CLoadMgr::GetInstance()->UnloadForTitleScene();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_LOBBY_SCENE)
			CLoadMgr::GetInstance()->UnloadForLobbyScene();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_PLAY_SCENE)
			CLoadMgr::GetInstance()->UnloadForPlayScene();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_BARBARIAN_MALE)
			CLoadMgr::GetInstance()->UnloadForBarbarianMale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_DEMONHUNTER_MALE)
			CLoadMgr::GetInstance()->UnloadForDemonHunterMale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_MONK_MALE)
			CLoadMgr::GetInstance()->UnloadForMonkMale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_WITCHDOCTOR_MALE)
			CLoadMgr::GetInstance()->UnloadForWitchDoctorMale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_WIZARD_MALE)
			CLoadMgr::GetInstance()->UnloadForWizardMale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_BARBARIAN_FEMALE)
			CLoadMgr::GetInstance()->UnloadForBarbarianFemale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_DEMONHUNTER_FEMALE)
			CLoadMgr::GetInstance()->UnloadForDemonHunterFemale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_MONK_FEMALE)
			CLoadMgr::GetInstance()->UnloadForMonkFemale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_WITCHDOCTOR_FEMALE)
			CLoadMgr::GetInstance()->UnloadForWitchDoctorFemale();
		else if(m_UnloadVec[i] == UNLOAD_TYPE_WIZARD_FEMALE)
			CLoadMgr::GetInstance()->UnloadForWizardFemale();
	}

	// LoadVec
	for(size_t i = 0; i < m_LoadVec.size(); ++i)
	{
		if(m_LoadVec[i] == LOAD_TYPE_BASE)
			CLoadMgr::GetInstance()->LoadForBase();
		else if(m_LoadVec[i] == LOAD_TYPE_TITLE_SCENE)
			CLoadMgr::GetInstance()->LoadForTitleScene();
		else if(m_LoadVec[i] == LOAD_TYPE_LOBBY_SCENE)
			CLoadMgr::GetInstance()->LoadForLobbyScene();
		else if(m_LoadVec[i] == LOAD_TYPE_PLAY_SCENE)
			CLoadMgr::GetInstance()->LoadForPlayScene();
		else if(m_LoadVec[i] == LOAD_TYPE_BARBARIAN_MALE)
			CLoadMgr::GetInstance()->LoadForBarbarianMale();
		else if(m_LoadVec[i] == LOAD_TYPE_DEMONHUNTER_MALE)
			CLoadMgr::GetInstance()->LoadForDemonHunterMale();
		else if(m_LoadVec[i] == LOAD_TYPE_MONK_MALE)
			CLoadMgr::GetInstance()->LoadForMonkMale();
		else if(m_LoadVec[i] == LOAD_TYPE_WITCHDOCTOR_MALE)
			CLoadMgr::GetInstance()->LoadForWitchDoctorMale();
		else if(m_LoadVec[i] == LOAD_TYPE_WIZARD_MALE)
			CLoadMgr::GetInstance()->LoadForWizardMale();
		else if(m_LoadVec[i] == LOAD_TYPE_BARBARIAN_FEMALE)
			CLoadMgr::GetInstance()->LoadForBarbarianFemale();
		else if(m_LoadVec[i] == LOAD_TYPE_DEMONHUNTER_FEMALE)
			CLoadMgr::GetInstance()->LoadForDemonHunterFemale();
		else if(m_LoadVec[i] == LOAD_TYPE_MONK_FEMALE)
			CLoadMgr::GetInstance()->LoadForMonkFemale();
		else if(m_LoadVec[i] == LOAD_TYPE_WITCHDOCTOR_FEMALE)
			CLoadMgr::GetInstance()->LoadForWitchDoctorFemale();
		else if(m_LoadVec[i] == LOAD_TYPE_WIZARD_FEMALE)
			CLoadMgr::GetInstance()->LoadForWizardFemale();
	}

	return CScene::UpdateLoad();
}
CScene* CLoadScene::UpdateComplete()
{
	return CScene::UpdateComplete();
}
CScene* CLoadScene::UpdatePlay()
{
	return m_pNextScene;
}