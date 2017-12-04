#include "StdAfx.h"
#include "Skeleton_SwordTrailEffect.h"

CSkeleton_SwordTrailEffect::CSkeleton_SwordTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect(_tszObjKey, _eObjType, 100, _pMatrix, &D3DXVECTOR3(-100.0f, 0.0f, 00.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.01f, _T("Skeleton_SwordTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CSkeleton_SwordTrailEffect::~CSkeleton_SwordTrailEffect(void)
{
	Release();
}

void CSkeleton_SwordTrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CSkeleton_SwordTrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CSkeleton_SwordTrailEffect::Render()
{
	CTrailEffect::Render();
}

void CSkeleton_SwordTrailEffect::Release()
{

}