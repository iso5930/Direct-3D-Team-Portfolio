#include "StdAfx.h"
#include "Monk_Serenity_BlastWaveEffect.h"

CMonk_Serenity_BlastWaveEffect::CMonk_Serenity_BlastWaveEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Serenity_BlastWave"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

	m_fAlpha = 0.f;
}

CMonk_Serenity_BlastWaveEffect::~CMonk_Serenity_BlastWaveEffect(void)
{
	Release();
}

void CMonk_Serenity_BlastWaveEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CMonk_Serenity_BlastWaveEffect::Update()
{
	CEffect::Update();

	m_fAlpha += 3.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 0.f, 1.f) * 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CMonk_Serenity_BlastWaveEffect::Render()
{
	CEffect::Render();
}

void CMonk_Serenity_BlastWaveEffect::Release()
{

}
