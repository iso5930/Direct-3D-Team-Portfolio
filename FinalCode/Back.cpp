#include "StdAfx.h"
#include "Back.h"

CBack::CBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszTexKey)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_BACK);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_BACK);
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _tszTexKey);
	AddComponent(pMaterialCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Screen"));
	AddComponent(pBufferCom);
}

CBack::~CBack()
{
	Release();
}

void CBack::Initialize()
{
	CObject::Initialize();
}

int CBack::Update()
{
	CObject::Update();

	return 0;
}

void CBack::Render()
{
	CObject::Render();
}

void CBack::Release()
{
}