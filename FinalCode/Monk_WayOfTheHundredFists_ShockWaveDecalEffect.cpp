#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_ShockWaveDecalEffect.h"

CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::CMonk_WayOfTheHundredFists_ShockWaveDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
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
	pRenderCom->m_dwPass = 7; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_WayOfTheHundredFists_ShockWaveDecal"));
	AddComponent(pMaterialCom);	

	m_fTime = 0.f;
}

CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::~CMonk_WayOfTheHundredFists_ShockWaveDecalEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_WayOfTheHundredFists_ShockWaveDecalEffect::Release()
{

}
