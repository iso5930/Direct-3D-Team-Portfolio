#include "StdAfx.h"
#include "Monk_SweepingWind_RingEffect.h"

CMonk_SweepingWind_RingEffect::CMonk_SweepingWind_RingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Salvation_Nova"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.f));
	AddComponent(m_pCollisionCom);

	m_fTime = 0.f;
	m_iMaxCnt = 99999999;
	m_fDamageTime = 0.f;
	m_fCoef = 0.175f;
}

CMonk_SweepingWind_RingEffect::~CMonk_SweepingWind_RingEffect(void)
{
	Release();
}

void CMonk_SweepingWind_RingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_fAlpha = 0.5f;
}

int CMonk_SweepingWind_RingEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fDamageTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fDamageTime >= 1.f)
	{
		m_fDamageTime = 0.f;

		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}

	if(m_iCnt > 0)
	{
		m_fTime = 0.f;
		m_iCnt = 0;
	}

	if(m_fTime >= 6.f)
	{
		Destroy();
	}

	m_pTransformCom->m_vAngle.y += D3DXToRadian(180.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_mWorld *= ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	return 0;
}

void CMonk_SweepingWind_RingEffect::Render()
{
	CEffect::Render();
}

void CMonk_SweepingWind_RingEffect::Release()
{

}