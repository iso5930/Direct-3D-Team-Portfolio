#include "StdAfx.h"
#include "Model.h"

CModel::CModel(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBoots, TCHAR* _tszHair, TCHAR* _tszHands, TCHAR* _tszPants, TCHAR* _tszUpper)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_MODEL);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_MODEL);
	AddComponent(pRenderCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_tszBoots);
	pBufferCom->AddBuffer(_tszHair);
	pBufferCom->AddBuffer(_tszHands);
	pBufferCom->AddBuffer(_tszPants);
	pBufferCom->AddBuffer(_tszUpper);
	AddComponent(pBufferCom);
}

CModel::~CModel()
{
	Release();
}

void CModel::Initialize()
{
	CObject::Initialize();
}

int CModel::Update()
{
	CObject::Update();

	return 0;
}

void CModel::Render()
{
	CObject::Render();
}

void CModel::Release()
{
}