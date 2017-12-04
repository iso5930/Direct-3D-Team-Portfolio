#include "StdAfx.h"
#include "Gate.h"

CGate::CGate(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText, TCHAR* _tszMapKey, D3DXVECTOR3* _pPos, D3DXVECTOR3* _pAngle, D3DXVECTOR3* _pSize, SCENE_TYPE _eSceneType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	//m_pBufferCom->AddBuffer(_T("Prob_Tristram_Stash"));
	m_pBufferCom->AddBuffer(_T("AlphaBox"));

	// ProbType
	m_eProbType = PROB_TYPE_GATE;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _tszText);

	// MapKey
	_tcscpy_s(m_tszMapKey, MIN_STR, _tszMapKey);

	// Pos
	m_vPos = *_pPos;

	// Angle
	m_vAngle = *_pAngle;

	// Size
	m_vSize = * _pSize;

	// SceneType
	m_eSceneType = _eSceneType;
}

CGate::~CGate()
{
	Release();
}

void CGate::Initialize()
{
	CStaticProb::Initialize();

	// Remove RenderCom
	//RemoveComponent(COM_TYPE_RENDER);
}

int CGate::Update()
{
	CStaticProb::Update();

	return 0;
}

void CGate::Render()
{
	CStaticProb::Render();
}

void CGate::Release()
{
}

void CGate::Event()
{
	// Find Player
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

	// Player
	CPlayer* pPlayer = (CPlayer*)pFindObject;

	// MapKey
	Info* pInfo = pPlayer->GetInfo();
	_tcscpy_s(pInfo->tszMapKey, MIN_STR, m_tszMapKey);

	CScene* pScene;
	switch(m_eSceneType)
	{
	case PLAYSCENE_TYPE_TRISTRAM:
		pScene = new CPlayScene_Tristram(CSceneMgr::GetInstance()->GetScene());
		break;

	case PLAYSCENE_TYPE_CATHEDRAL_F1:
		pScene = new CPlayScene_Cathedral_F1(CSceneMgr::GetInstance()->GetScene());
		break;

	case PLAYSCENE_TYPE_CATHEDRAL_F2:
		pScene = new CPlayScene_Cathedral_F2(CSceneMgr::GetInstance()->GetScene());
		break;

	case PLAYSCENE_TYPE_CATHEDRAL_F3:
		pScene = new CPlayScene_Cathedral_F3(CSceneMgr::GetInstance()->GetScene());
		break;

	case PLAYSCENE_TYPE_CATHEDRAL_F4:
		pScene = new CPlayScene_Cathedral_F4(CSceneMgr::GetInstance()->GetScene());
		break;

	case PLAYSCENE_TYPE_ROYAL_CHAMBER:
		pScene = new CPlayScene_RoyalChamber(CSceneMgr::GetInstance()->GetScene());
		break;
	case PLAYSCENE_TYPE_REORIK_MANSION:
		pScene = new CPlayScene_ReorikMansion(CSceneMgr::GetInstance()->GetScene());
		break;
	}

	// SetNextScene
	CSceneMgr::GetInstance()->SetNextScene(pScene, true, &m_vPos, &m_vAngle, &m_vSize);
}

void CGate::EventEnd()
{
}