#include "StdAfx.h"
#include "Monk_CycloneStrike_NovaEffect.h"

CMonk_CycloneStrike_NovaEffect::CMonk_CycloneStrike_NovaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_CycloneStrike_Nova"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 21;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_BreathOfHeaven_Alpha"));
	AddComponent(pMaterialCom);

	m_fAlpha = 0.5f;
	m_fTime = 0.f;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.f));
	AddComponent(pCollisionCom);

	m_fCoef = 0.1f;

	m_iMaxCnt = 99999;

	m_eSkillType = SKILL_TYPE_FULL;
}

CMonk_CycloneStrike_NovaEffect::~CMonk_CycloneStrike_NovaEffect(void)
{
	Release();
}

void CMonk_CycloneStrike_NovaEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(15.f, 1.f, 15.f);
}

int CMonk_CycloneStrike_NovaEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CYCLONE_STRIKE1.ogg"));

		CMonk_CycloneStrike_NovaRevEffect* pNovaRevEffect = new CMonk_CycloneStrike_NovaRevEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pNovaRevEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pNovaRevEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pNovaRevEffect->Initialize();
	}

	return 0;
}

void CMonk_CycloneStrike_NovaEffect::Render()
{
	CEffect::Render();
}

void CMonk_CycloneStrike_NovaEffect::Release()
{

}
