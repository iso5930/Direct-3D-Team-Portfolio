#include "StdAfx.h"
#include "Monk_DeadlyReach_AfterImageEffect.h"

CMonk_DeadlyReach_AfterImageEffect::CMonk_DeadlyReach_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WayOfTheHundredFists_Shadow"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

	m_vDir = _vDir;
	m_fAlpha = 1.f;
	m_fTime = 0.f;
	m_iMode = 0;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 1.5f;
}

CMonk_DeadlyReach_AfterImageEffect::~CMonk_DeadlyReach_AfterImageEffect(void)
{
	Release();
}

void CMonk_DeadlyReach_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
}

int CMonk_DeadlyReach_AfterImageEffect::Update()
{
	CEffect::Update();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1: 
		Mode2();
		break;
	}

	return 0;
}

void CMonk_DeadlyReach_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CMonk_DeadlyReach_AfterImageEffect::Release()
{

}

void CMonk_DeadlyReach_AfterImageEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.15f)
	{
		++m_iMode;
		m_fAlpha = 0.f;
	}
}

void CMonk_DeadlyReach_AfterImageEffect::Mode2()
{
	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 4.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();
}