#include "StdAfx.h"
#include "Monk_WaveOfLight_WaveEffect.h"

CMonk_WaveOfLight_WaveEffect::CMonk_WaveOfLight_WaveEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 4; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_WayOfTheHundredFists_ShockWaveDecal"));
	AddComponent(pMaterialCom);	

	m_fTime = 0.f;
}

CMonk_WaveOfLight_WaveEffect::~CMonk_WaveOfLight_WaveEffect(void)
{
	Release();
}

void CMonk_WaveOfLight_WaveEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CMonk_WaveOfLight_WaveEffect::Update()
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

void CMonk_WaveOfLight_WaveEffect::Render()
{
	CEffect::Render();
}

void CMonk_WaveOfLight_WaveEffect::Release()
{

}
