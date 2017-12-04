#include "Stdafx.h"
#include "SceneMgr.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
{
	// Destroy
	m_bDestroy = false;

	// Scene
	m_pScene = NULL;

	// NextScene
	m_pNextScene = NULL;

	// InPlay
	m_bInPlay = false;

	// NextPos
	ZeroMemory(&m_vNextPos, sizeof(D3DXVECTOR3));

	// NextAngle
	ZeroMemory(&m_vNextAngle, sizeof(D3DXVECTOR3));

	// NextSize
	ZeroMemory(&m_vNextSize, sizeof(D3DXVECTOR3));
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize(CScene* _pScene)
{
	// Scene
	m_pScene = _pScene;
	m_pScene->Initialize();
}

int CSceneMgr::Update()
{
	if(m_bDestroy)
		return 1;

	CScene* pScene = NULL;

	if(m_pScene != NULL)
		pScene = m_pScene->Update();

	if(pScene != NULL)
	{
		delete m_pScene;
		m_pScene = pScene;
		m_pScene->Initialize();
	}

	if(m_pNextScene != NULL)
	{
		if(m_bInPlay == false)
		{
			m_pScene->Destroy();
		}
		else
		{
			CObject* pFindObject = NULL;
			m_pScene->GetLayer(LAYER_TYPE_PLAYER)->FindObject(pFindObject, _T("Player"));

			CTransformCom* pTransformCom = (CTransformCom*)pFindObject->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_vNextPos;
			pTransformCom->m_vAngle = m_vNextAngle;
			pTransformCom->m_vSize = m_vNextSize;
		}
		m_bInPlay = false;

		delete m_pScene;
		m_pScene = m_pNextScene;
		m_pNextScene = NULL;
		m_pScene->Initialize();
	}

	return 0;
}

void CSceneMgr::Render()
{
	if(m_pScene != NULL)
		m_pScene->Render();
}

void CSceneMgr::Release()
{
	if(m_pScene != NULL)
	{
		m_pScene->Destroy();
		delete m_pScene;
		m_pScene = NULL;
	}

	if(m_pNextScene != NULL)
	{
		m_pNextScene->Destroy();
		delete m_pNextScene;
		m_pNextScene = NULL;
	}
}

void CSceneMgr::SetNextScene(CScene* _pNextScene, bool _bInPlay, D3DXVECTOR3* _pNextPos /*= NULL*/, D3DXVECTOR3* _pNextAngle /*= NULL*/, D3DXVECTOR3* _pNextSize /*= NULL*/)
{
	// NextScene
	m_pNextScene = _pNextScene;

	// InPlay
	m_bInPlay = _bInPlay;

	// NextPos
	if(_pNextPos != NULL)
		m_vNextPos = *_pNextPos;

	// NextAngle
	if(_pNextAngle != NULL)
		m_vNextAngle = *_pNextAngle;

	// NextSize
	if(_pNextSize != NULL)
		m_vNextSize = *_pNextSize;
}
