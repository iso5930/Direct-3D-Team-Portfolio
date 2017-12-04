#include "StdAfx.h"
#include "ZombieFemale_PukeGroundDecal.h"

CZombieFemale_PukeGroundDecal::CZombieFemale_PukeGroundDecal(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7 ; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	int iRand = rand() % 3;

	if(iRand == 0)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("PukeDecal0"));
		AddComponent(pMaterialCom);
	}	

	if(iRand == 1)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("PukeDecal1"));
		AddComponent(pMaterialCom);
	}

	if(iRand == 2)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("PukeDecal2"));
		AddComponent(pMaterialCom);
	}

	m_fTime = 0.f;
}

CZombieFemale_PukeGroundDecal::~CZombieFemale_PukeGroundDecal(void)
{
	Release();
}

void CZombieFemale_PukeGroundDecal::Initialize()
{
	CEffect::Initialize();
}

int CZombieFemale_PukeGroundDecal::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() * 0.2f;

	if(m_fTime > 2.f)
		Destroy();

	return 0;
}

void CZombieFemale_PukeGroundDecal::Render()
{
	CEffect::Render();
}

void CZombieFemale_PukeGroundDecal::Release()
{

}
