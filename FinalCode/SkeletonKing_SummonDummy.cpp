#include "StdAfx.h"
#include "SkeletonKing_SummonDummy.h"

CSkeletonKing_SummonDummy::CSkeletonKing_SummonDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vEndPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vEndPos = *_vEndPos;
	m_fDetail = 0.f;
	
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_pTrailEffect = NULL;	
}

CSkeletonKing_SummonDummy::~CSkeletonKing_SummonDummy(void)
{
	Release();
}


void CSkeletonKing_SummonDummy::Initialize()
{
	CEffect::Initialize();

	D3DXVec3TransformCoord(&m_vStartPos, &m_pTransformCom->m_vPos,  &((CSkeleton_King*)m_pOwner)->m_LeftHandBone.mWorld);

	D3DXVECTOR3 vCenter = (m_vEndPos - m_vStartPos) / 2.f;
	vCenter = m_vStartPos + vCenter;

	D3DXVECTOR3 vDir;

	D3DXVec3Normalize(&vDir, &vCenter);

	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);

	vUp = vUp * 70;

	m_vBezierPos = vCenter + vUp;
}	

int CSkeletonKing_SummonDummy::Update()
{
	CEffect::Update();

	m_fDetail += (1.f / 40.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_fTime = m_fDetail;


	m_pTransformCom->m_vPos = GetBezier(m_vStartPos, m_vBezierPos, m_vEndPos, m_fDetail);

	if(m_fTime > 0.01f)
	{
		m_pTrailEffect = new CSkeletonKing_EctoplasmBase(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
		m_pTrailEffect->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pTrailEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 50.f);
		m_fTime = 0.0f;
	}

	if(m_fDetail >= 1.f)
	{
		D3DXVECTOR3 vTempPos = m_pTransformCom->m_vPos;
		vTempPos.y += 40;

		CSkeletonKing_SummonCompelete* pSummonComplete = new CSkeletonKing_SummonCompelete(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vTempPos, true);
		m_pOwner->GetLayer()->AddObject(pSummonComplete, LAYER_TYPE_EFFECT);
		pSummonComplete->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)pSummonComplete->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);

		int iRandY = rand() % 100;
		int iRandY2 = rand() % 100;
		int iRandY3 = rand() % 100;
		int iRandY4 = rand() % 100;
		int iSize = rand() % 30 + 20;
		int iSize2 = rand() % 30 + 20;
		int iSize3 = rand() % 30 + 20;
		int iSize4 = rand() % 30 + 20;

		vTempPos = m_pTransformCom->m_vPos;
		vTempPos.x += 10;
		vTempPos.z += 10;
		vTempPos.y += (float)iRandY;
		pSummonComplete = new CSkeletonKing_SummonCompelete(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vTempPos);
		m_pOwner->GetLayer()->AddObject(pSummonComplete, LAYER_TYPE_EFFECT);
		pSummonComplete->Initialize();

		pTransformCom = (CTransformCom*)pSummonComplete->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3((float)iSize, (float)iSize, (float)iSize);

		vTempPos = m_pTransformCom->m_vPos;
		vTempPos.x += 10;
		vTempPos.z -= 10;
		vTempPos.y += (float)iRandY2;
		pSummonComplete = new CSkeletonKing_SummonCompelete(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vTempPos);
		m_pOwner->GetLayer()->AddObject(pSummonComplete, LAYER_TYPE_EFFECT);
		pSummonComplete->Initialize();

		pTransformCom = (CTransformCom*)pSummonComplete->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3((float)iSize2, (float)iSize2, (float)iSize2);


		vTempPos = m_pTransformCom->m_vPos;
		vTempPos.x -= 10;
		vTempPos.z -= 10;
		vTempPos.y += (float)iRandY3;
		pSummonComplete = new CSkeletonKing_SummonCompelete(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vTempPos);
		m_pOwner->GetLayer()->AddObject(pSummonComplete, LAYER_TYPE_EFFECT);
		pSummonComplete->Initialize();

		pTransformCom = (CTransformCom*)pSummonComplete->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3((float)iSize3, (float)iSize3, (float)iSize3);


		vTempPos = m_pTransformCom->m_vPos;
		vTempPos.x -= 10;
		vTempPos.z += 10;
		vTempPos.y += (float)iRandY4;
		pSummonComplete = new CSkeletonKing_SummonCompelete(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vTempPos);
		m_pOwner->GetLayer()->AddObject(pSummonComplete, LAYER_TYPE_EFFECT);
		pSummonComplete->Initialize();

		pTransformCom = (CTransformCom*)pSummonComplete->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize= D3DXVECTOR3((float)iSize4, (float)iSize4, (float)iSize4);

		Destroy();
	}

	return 0;
}

void CSkeletonKing_SummonDummy::Render()
{
	CEffect::Render();
}

void CSkeletonKing_SummonDummy::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}

D3DXVECTOR3 CSkeletonKing_SummonDummy::GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail)
{
	D3DXVECTOR3 vResult = D3DXVECTOR3(0.f, 0.f, 0.f);

	vResult.x = _v3.x * (_fDetail * _fDetail) + _v2.x * (2 * _fDetail * (1 - _fDetail)) + _v1.x * ((1 - _fDetail) * (1 - _fDetail));
	vResult.y = _v3.y * (_fDetail * _fDetail) + _v2.y * (2 * _fDetail * (1 - _fDetail)) + _v1.y * ((1 - _fDetail) * (1 - _fDetail));
	vResult.z = _v3.z * (_fDetail * _fDetail) + _v2.z * (2 * _fDetail * (1 - _fDetail)) + _v1.z * ((1 - _fDetail) * (1 - _fDetail));

	return vResult;
}
