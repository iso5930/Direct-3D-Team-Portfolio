#include "StdAfx.h"
#include "SeamlessMgr.h"

IMPLEMENT_SINGLETON(CSeamlessMgr)

CSeamlessMgr::CSeamlessMgr()
{
	// Enable
	m_bEnable = false;

	// Destroy
	m_bDestroy = false;

	// Zone
	m_iZone = 0;

	// MapKey
	ZeroMemory(m_tszMapKey, sizeof(m_tszMapKey));

	// LoadThread
	m_hLoadThread = (HANDLE)_beginthreadex(NULL, 0, LoadThread, this, CREATE_SUSPENDED, NULL);
	SetThreadPriority(m_hLoadThread, THREAD_PRIORITY_LOWEST);

	// ClearThread
	m_hClearThread = (HANDLE)_beginthreadex(NULL, 0, ClearThread, this, CREATE_SUSPENDED, NULL);
	SetThreadPriority(m_hClearThread, THREAD_PRIORITY_LOWEST);

	// CS
	m_pInCS = new CRITICAL_SECTION;
	m_pOutCS = new CRITICAL_SECTION;
	InitializeCriticalSection(m_pInCS);
	InitializeCriticalSection(m_pOutCS);
	EnterCriticalSection(m_pInCS);
	EnterCriticalSection(m_pOutCS);

	// Mode
	m_iMode = 0;
}

CSeamlessMgr::~CSeamlessMgr()
{
	Release();
}

void CSeamlessMgr::Initialize()
{
}

int CSeamlessMgr::Update()
{
	// If be Disabled, return..
	if(m_bEnable == false)
		return 0;

	switch(m_iMode)
	{
	case 0:
		WaitClearThread();
		break;

	case 1:
		WaitOutCSInClearThread();
		break;

	case 2:
		CompleteClearThread();
		break;

	case 3:
		WaitLoadThread();
		break;

	case 4:
		WaitOutCSInLoadThread();
		break;

	case 5:
		CompleteLoadThread();
		break;
	}

	return 0;
}

void CSeamlessMgr::Render()
{
}

void CSeamlessMgr::Release()
{
	// Destroy
	m_bDestroy = true;

	// Thread
	LeaveCriticalSection(m_pInCS);
	LeaveCriticalSection(m_pOutCS);

	ResumeThread(m_hClearThread);
	ResumeThread(m_hLoadThread);
	WaitForSingleObject(m_hLoadThread, INFINITE);
	WaitForSingleObject(m_hClearThread, INFINITE);
	CloseHandle(m_hLoadThread);
	CloseHandle(m_hClearThread);
	m_hLoadThread = NULL;
	m_hClearThread = NULL;

	// CS
	DeleteCriticalSection(m_pInCS);
	DeleteCriticalSection(m_pOutCS);
	delete m_pInCS;
	delete m_pOutCS;

	// ClearVec
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_ClearVec[i].size(); ++j)
			delete[] m_ClearVec[i][j];
		m_ClearVec[i].clear();
	}
}

////////////////////////////////////////////////////////////////////////// OutFunction
void CSeamlessMgr::Enable()
{
	// Enable
	m_bEnable = true;

	// Player
	CObject* pPlayer = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_PLAYER)->FindObject(pPlayer, _T("Player"));

	// MapKey
	Info* pInfo = ((CPlayer*)pPlayer)->GetInfo();
	_tcscpy_s(m_tszMapKey, MIN_STR, pInfo->tszMapKey);

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Zone
	int iZoneX = int(pTransformCom->m_vPos.x / 3060.0f);
	int iZoneZ = int(pTransformCom->m_vPos.z / 3060.0f);
	m_iZone = iZoneZ * 100 + iZoneX;

	// Process
	unordered_map<int, vector<int>>::iterator Find_Iter = m_NodeMap.find(m_iZone);
	TCHAR tszPath[MAX_STR] = _T("../Resource/Mesh/Map/");
	_tcscat_s(tszPath, MAX_STR, m_tszMapKey);
	_tcscat_s(tszPath, MAX_STR, _T("/"));

	for(size_t i = 0; i < Find_Iter->second.size(); ++i)
	{
		TCHAR tszZone[MIN_STR];
		_itot_s(Find_Iter->second[i], tszZone, 10);

		TCHAR tszBufKey[MIN_STR];
		_tcscpy_s(tszBufKey, MIN_STR, m_tszMapKey);
		_tcscat_s(tszBufKey, MIN_STR, tszZone);

		TCHAR tszFile[MIN_STR];
		_tcscpy_s(tszFile, MIN_STR, tszZone);
		_tcscat_s(tszFile, MIN_STR, _T(".X"));

		CMap* pMap = new CMap(_T("Map"), OBJ_TYPE_DYNAMIC, tszBufKey, tszPath, tszFile);
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_MAP)->AddObject(pMap);
		CTransformCom* pTransformCom = (CTransformCom*)pMap->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(3060.0f * (Find_Iter->second[i] % 100), 0.0f, 3060.0f * (Find_Iter->second[i] / 100));
		pMap->Initialize();
	}
}

void CSeamlessMgr::Disable()
{
	// Wait Complete Mode
	while(m_iMode != 0 && m_iMode != 3)
		Update();

	// Disable
	m_bEnable = false;

	// Mode
	m_iMode = 0;

	// NodeMap
	unordered_map<int, vector<int>>::iterator Iter = m_NodeMap.begin();
	unordered_map<int, vector<int>>::iterator IterEnd = m_NodeMap.end();
	for(; Iter != IterEnd; ++Iter)
		Iter->second.clear();
	m_NodeMap.clear();

	// ClearVec
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_ClearVec[i].size(); ++j)
		{
			CBufferMgr::GetInstance()->RemoveBuffer(m_ClearVec[i][j]);
			delete[] m_ClearVec[i][j];
		}
		m_ClearVec[i].clear();
	}
}

void CSeamlessMgr::AddNode(int _iKey, int _iZone)
{
	unordered_map<int, vector<int>>::iterator Find_Iter = m_NodeMap.find(_iKey);
	if(Find_Iter == m_NodeMap.end())
	{
		vector<int> NodeVec;
		NodeVec.push_back(_iZone);
		m_NodeMap.insert(unordered_map<int, vector<int>>::value_type(_iKey, NodeVec));
	}
	else
		Find_Iter->second.push_back(_iZone);
}

void CSeamlessMgr::RemoveMapBuffer(TCHAR* _tszBufKey)
{
	TCHAR* tszBufKey = new TCHAR[MIN_STR];
	_tcscpy_s(tszBufKey, MIN_STR, _tszBufKey);
	m_ClearVec[0].push_back(tszBufKey);
}

////////////////////////////////////////////////////////////////////////// InFunction
// Mode0
void CSeamlessMgr::WaitClearThread()
{
	if(m_ClearVec[0].size() == 0)
	{
		// WaitLoadThread Mode
		m_iMode = 3;
		return;
	}

	// Dump Mode
	m_iMode = -1;

	// Copy
	for(size_t i = 0; i < m_ClearVec[0].size(); ++i)
		m_ClearVec[1].push_back(m_ClearVec[0][i]);
	m_ClearVec[0].clear();

	// Resume ClearThread
	ResumeThread(m_hClearThread);

	// InCS Unlock
	LeaveCriticalSection(m_pInCS);
}

// Mode1
void CSeamlessMgr::WaitOutCSInClearThread()
{
	// Dump Mode
	m_iMode = -1;

	// InCS Lock
	EnterCriticalSection(m_pInCS);

	// OutCS Unlock
	LeaveCriticalSection(m_pOutCS);
}

// Mode2
void CSeamlessMgr::CompleteClearThread()
{
	// WaitLoadThread Mode
	m_iMode = 3;

	// Suspend ClearThread
	SuspendThread(m_hClearThread);

	// OutCS Lock
	EnterCriticalSection(m_pOutCS);
}

// Mode3
void CSeamlessMgr::WaitLoadThread()
{
	// Player
	CObject* pPlayer = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_PLAYER)->FindObject(pPlayer, _T("Player"));

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Zone
	int iZoneX = int(pTransformCom->m_vPos.x / 3060.0f);
	int iZoneZ = int(pTransformCom->m_vPos.z / 3060.0f);
	int iZone = iZoneZ * 100 + iZoneX;

	if(m_iZone == iZone)
	{
		// WaitClearThread Mode
		m_iMode = 0;
		return;
	}

	// Dump Mode
	m_iMode = -1;

	// Zone
	m_iZone = iZone;

	// Resume LoadThread
	ResumeThread(m_hLoadThread);

	// InCS Unlock
	LeaveCriticalSection(m_pInCS);
}

// Mode4
void CSeamlessMgr::WaitOutCSInLoadThread()
{
	// Dump Mode
	m_iMode = -1;

	// InCS Lock
	EnterCriticalSection(m_pInCS);

	// OutCS Unlock
	LeaveCriticalSection(m_pOutCS);
}

// Mode5
void CSeamlessMgr::CompleteLoadThread()
{
	// WaitClearThread Mode
	m_iMode = 0;

	// Suspend LoadThread
	SuspendThread(m_hLoadThread);

	// OutCS Lock
	EnterCriticalSection(m_pOutCS);
}

////////////////////////////////////////////////////////////////////////// Thread
UINT WINAPI CSeamlessMgr::ClearThread(LPVOID _pParam)
{
	CSeamlessMgr* pSeamlessMgr = (CSeamlessMgr*)_pParam;
	pSeamlessMgr->Clear();

	return 0;
}

void CSeamlessMgr::Clear()
{
	while(1)
	{
		EnterCriticalSection(m_pInCS);
		LeaveCriticalSection(m_pInCS);

		// Destroy
		if(m_bDestroy)
			break;

		// Process
		for(size_t i = 0; i < m_ClearVec[1].size(); ++i)
		{
			CBufferMgr::GetInstance()->RemoveBuffer(m_ClearVec[1].at(i));
			delete[] m_ClearVec[1][i];
		}
		m_ClearVec[1].clear();

		// WaitOutCSInClear Mode
		m_iMode = 1;
		EnterCriticalSection(m_pOutCS);
		LeaveCriticalSection(m_pOutCS);

		// CompleteClearThread Mode
		m_iMode = 2;
	}
}

UINT WINAPI CSeamlessMgr::LoadThread(LPVOID _pParam)
{
	CSeamlessMgr* pSeamlessMgr = (CSeamlessMgr*)_pParam;
	pSeamlessMgr->Load();

	return 0;
}

void CSeamlessMgr::Load()
{
	while(1)
	{
		EnterCriticalSection(m_pInCS);
		LeaveCriticalSection(m_pInCS);

		// Destroy
		if(m_bDestroy)
			break;

		// Process
		unordered_map<int, vector<int>>::iterator Find_Iter = m_NodeMap.find(m_iZone);

		TCHAR tszTemp[MIN_STR];
		TCHAR** tszZone = new TCHAR*[Find_Iter->second.size()];
		TCHAR** tszBufKey = new TCHAR*[Find_Iter->second.size()];
		for(size_t i = 0; i < Find_Iter->second.size(); ++i)
		{
			// Zone
			tszZone[i] = new TCHAR[MIN_STR];
			_itot_s(Find_Iter->second[i], tszTemp, 10);
			_tcscpy_s(tszZone[i], MIN_STR, tszTemp);

			// BufKey
			tszBufKey[i] = new TCHAR[MIN_STR];
			_tcscpy_s(tszBufKey[i], MIN_STR, m_tszMapKey);
			_tcscat_s(tszBufKey[i], MIN_STR, tszZone[i]);
		}

		vector<CObject*> MapVec;
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_MAP)->FindObjects(MapVec, _T("Map"));

		vector<CObject*> RemoveVec;
		for(size_t i = 0; i < MapVec.size(); ++i)
		{
			CMap* pMap = (CMap*)MapVec[i];
			bool bFind = false;
			
			for(size_t j = 0; j < Find_Iter->second.size() && !bFind; ++j)
			{
				if(_tcscmp(pMap->GetBufKey(), tszBufKey[j]) == 0)
					bFind = true;
			}

			if(!bFind)
				RemoveVec.push_back(pMap);
		}

		TCHAR tszPath[MAX_STR] = _T("../Resource/Mesh/Map/");
		_tcscat_s(tszPath, MAX_STR, m_tszMapKey);
		_tcscat_s(tszPath, MAX_STR, _T("/"));

		for(size_t i = 0; i < Find_Iter->second.size(); ++i)
		{
			bool bFind = false;

			for(size_t j = 0; j < MapVec.size() && !bFind; ++j)
			{
				CMap* pMap = (CMap*)MapVec[j];
				if(_tcscmp(tszBufKey[i], pMap->GetBufKey()) == 0)
					bFind = true;
			}

			if(!bFind)
			{
				TCHAR tszFile[MIN_STR];
				_tcscpy_s(tszFile, MIN_STR, tszZone[i]);
				_tcscat_s(tszFile, MIN_STR, _T(".X"));

				CMap* pMap = new CMap(_T("Map"), OBJ_TYPE_DYNAMIC, tszBufKey[i], tszPath, tszFile);
				CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_MAP)->AddObject(pMap);
				CTransformCom* pTransformCom = (CTransformCom*)pMap->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(3060.0f * (Find_Iter->second[i] % 100), 0.0f, 3060.0f * (Find_Iter->second[i] / 100));
				pMap->Initialize();
			}
		}

		for(size_t i = 0; i < RemoveVec.size(); ++i)
			RemoveVec[i]->Destroy();

		for(size_t i = 0; i < Find_Iter->second.size(); ++i)
		{
			delete[] tszZone[i];
			delete[] tszBufKey[i];
		}
		delete[] tszZone;
		delete[] tszBufKey;

		// WaitOutCSInLoadThread Mode
		m_iMode = 4;
		EnterCriticalSection(m_pOutCS);
		LeaveCriticalSection(m_pOutCS);

		// CompleteLoadThread Mode
		m_iMode = 5;
	}
}