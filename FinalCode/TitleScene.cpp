#include "StdAfx.h"
#include "TitleScene.h"

CTitleScene::CTitleScene(CScene* _pScene)
: CScene(_pScene)
{
	// Time
	m_fTime = 0.0f;
}

CTitleScene::~CTitleScene()
{
	Release();
}

void CTitleScene::Initialize()
{
	CScene::Initialize();
}

CScene* CTitleScene::Update()
{
	return CScene::Update();
}

void CTitleScene::Render()
{
	CScene::Render();
}

void CTitleScene::Release()
{
}

CScene* CTitleScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CTitleScene::UpdateComplete()
{
	// TitleSceneBack
	CTitleSceneBack* pTitleSceneBack = new CTitleSceneBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(pTitleSceneBack);
	pTitleSceneBack->Initialize();

	return CScene::UpdateComplete();
}

CScene* CTitleScene::UpdatePlay()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 6.0f)
		return new CLoginScene(this);

	return CScene::UpdatePlay();
}