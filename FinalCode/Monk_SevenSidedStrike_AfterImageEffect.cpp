#include "StdAfx.h"
#include "Monk_SevenSidedStrike_AfterImageEffect.h"

CMonk_SevenSidedStrike_AfterImageEffect::CMonk_SevenSidedStrike_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SevenSidedStrike"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 14;
	AddComponent(pRenderCom);

	m_fAlpha = 0.5f;
	m_fTime = 0.f;
	m_vDir = _vDir;
}

CMonk_SevenSidedStrike_AfterImageEffect::~CMonk_SevenSidedStrike_AfterImageEffect(void)
{
	Release();
}

void CMonk_SevenSidedStrike_AfterImageEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_SevenSidedStrike_AfterImageEffect::Update()
{
	CEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += fTime;

	if(m_fTime >= 0.35f)
	{
		Destroy();

		CMonk_SevenSidedStrike_FlashEffect* pFlahsEffect = new CMonk_SevenSidedStrike_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pFlahsEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFlahsEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y + D3DXToRadian(180.f);
		pFlahsEffect->Initialize();
	}

	m_pTransformCom->m_vPos += m_vDir * fTime;

	return 0;
}

void CMonk_SevenSidedStrike_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CMonk_SevenSidedStrike_AfterImageEffect::Release()
{

}
