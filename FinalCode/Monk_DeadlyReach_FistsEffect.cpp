#include "StdAfx.h"
#include "Monk_DeadlyReach_FistsEffect.h"

CMonk_DeadlyReach_FistsEffect::CMonk_DeadlyReach_FistsEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, float _fTime)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;
	m_fTime = 0.f;
	m_pTrailEffect = NULL;	

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fCreateTime = _fTime;
	m_iMode = 0;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 1.5f;
}

CMonk_DeadlyReach_FistsEffect::~CMonk_DeadlyReach_FistsEffect(void)
{
	Release();
}

void CMonk_DeadlyReach_FistsEffect::Initialize()
{
	CEffect::Initialize();	
}

int CMonk_DeadlyReach_FistsEffect::Update()
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

void CMonk_DeadlyReach_FistsEffect::Render()
{	
	CEffect::Render();
}

void CMonk_DeadlyReach_FistsEffect::Release()
{
	
}

void CMonk_DeadlyReach_FistsEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fCreateTime)
	{
		if (m_fTime > 0.45f)
		{
			CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("DEADLY_REACH3.ogg"));
		}
		m_fTime = 0.f;
		++m_iMode;

		m_pTrailEffect = new CMonk_DeadlyReach_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
		m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
		m_pTrailEffect->Initialize();
	}
}

void CMonk_DeadlyReach_FistsEffect::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();

		if(m_pTrailEffect != NULL)
		{
			m_pTrailEffect->Destroy();
			m_pTrailEffect = NULL;
		}
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
}	