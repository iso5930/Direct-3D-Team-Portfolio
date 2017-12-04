#include "Stdafx.h"
#include "Scene.h"

CScene::CScene(CScene* _pScene)
{
	// Mode
	m_dwMode = 0;

	// Thread
	m_hThread = NULL;

	// LoadBack
	m_pLoadBack = NULL;

	// Layer
	for(int i = 0; i < LAYER_TYPE_END; ++i)
	{
		CLayer* pLayer = NULL;
		if(_pScene != NULL)
			pLayer = _pScene->GetLayer((LAYER_TYPE)i);

		m_pLayer[i] = new CLayer(this, pLayer);
		m_pLayer[i]->Initialize();
	}
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	// Thread
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, LoadThread, this, 0, NULL);
}

CScene* CScene::Update()
{
	for(int i = 0; i < LAYER_TYPE_END; ++i)
		m_pLayer[i]->Update();

	switch(m_dwMode)
	{
	case 2:
		return UpdatePlay();

	case 1:
		return UpdateComplete();
	}

	return NULL;
}

void CScene::Render()
{
	for(int i = 0; i < LAYER_TYPE_END; ++i)
		m_pLayer[i]->Render();
}

void CScene::Release()
{
	// Thread
	if(m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	// Player Stop
	CObject* pFindObject = NULL;
	m_pLayer[LAYER_TYPE_PLAYER]->FindObject(pFindObject, _T("Player"));

	if(pFindObject != NULL)
	{
		CPlayer* pPlayer = (CPlayer*)pFindObject;
		pPlayer->Stop();
	}

	// Layer
	for(int i = 0; i < LAYER_TYPE_END; ++i)
		delete m_pLayer[i];
}

CScene* CScene::UpdateLoad()
{
	++m_dwMode;
	return NULL;
}

CScene* CScene::UpdateComplete()
{
	// Thread
	if(m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	// Player Run
	CObject* pFindObject = NULL;
	m_pLayer[LAYER_TYPE_PLAYER]->FindObject(pFindObject, _T("Player"));

	if(pFindObject != NULL)
	{
		CPlayer* pPlayer = (CPlayer*)pFindObject;
		pPlayer->Run();
	}

	// LoadBack
	if(m_pLoadBack != NULL)
	{
		m_pLoadBack->Destroy();
		m_pLoadBack = NULL;
	}

	++m_dwMode;
	return NULL;
}

CScene* CScene::UpdatePlay()
{
	return NULL;
}

UINT WINAPI CScene::LoadThread(LPVOID _pParam)
{
	// Load
	((CScene*)_pParam)->UpdateLoad();

	return 0;
}

CLayer* CScene::GetLayer(LAYER_TYPE _eLayerType)
{
	return m_pLayer[_eLayerType];
}

void CScene::Destroy()
{
	// Thread
	if(m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	// Layer
	for(int i = 0; i < LAYER_TYPE_END; ++i)
		m_pLayer[i]->Destroy();
}