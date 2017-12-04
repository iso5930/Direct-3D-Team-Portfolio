#include "StdAfx.h"
#include "SkeletonSummoner_SummonEffect.h"

CSkeletonSummoner_SummonEffect::CSkeletonSummoner_SummonEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vDestPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vEndPos = *_vDestPos;
	m_fDetail = 0.f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_pTrailEffect = NULL;
	m_pSummonSkeletonEffect = NULL;
}

CSkeletonSummoner_SummonEffect::~CSkeletonSummoner_SummonEffect(void)
{
	Release();
}

void CSkeletonSummoner_SummonEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CSkeletonSummoner_SummonTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	m_vStartPos = m_pTransformCom->m_vPos;

	D3DXVECTOR3 vCenter = (m_vEndPos - m_vStartPos) / 2.f;
	vCenter = m_vStartPos + vCenter;

	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, &vCenter);

	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);

	vUp = vUp * 70;

	m_vBezierPos = vCenter + vUp;
}

int CSkeletonSummoner_SummonEffect::Update()
{
	CEffect::Update();
	
	m_fDetail += (1.f / 40.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vPos = GetBezier(m_vStartPos, m_vBezierPos, m_vEndPos, m_fDetail);

	if(m_fDetail >= 1.f)
	{
		m_pSummonSkeletonEffect = new CSkeletonSummoner_SummonSkeleton(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_vPos);
		m_pLayer->AddObject(m_pSummonSkeletonEffect, LAYER_TYPE_EFFECT);
		m_pSummonSkeletonEffect->Initialize();

		Destroy();
		// 끝나는 위치에 도달했을때 이펙트 추가
	}

	return 0;
}

void CSkeletonSummoner_SummonEffect::Render()
{
	CEffect::Render();
}

void CSkeletonSummoner_SummonEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}

D3DXVECTOR3 CSkeletonSummoner_SummonEffect::GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail)
{
	D3DXVECTOR3 vResult = D3DXVECTOR3(0.f, 0.f, 0.f);

	vResult.x = _v3.x * (_fDetail * _fDetail) + _v2.x * (2 * _fDetail * (1 - _fDetail)) + _v1.x * ((1 - _fDetail) * (1 - _fDetail));
	vResult.y = _v3.y * (_fDetail * _fDetail) + _v2.y * (2 * _fDetail * (1 - _fDetail)) + _v1.y * ((1 - _fDetail) * (1 - _fDetail));
	vResult.z = _v3.z * (_fDetail * _fDetail) + _v2.z * (2 * _fDetail * (1 - _fDetail)) + _v1.z * ((1 - _fDetail) * (1 - _fDetail));

	return vResult;
}
