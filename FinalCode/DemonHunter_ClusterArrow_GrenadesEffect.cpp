#include "StdAfx.h"
#include "DemonHunter_ClusterArrow_GrenadesEffect.h"

CDemonHunter_ClusterArrow_GrenadesEffect::CDemonHunter_ClusterArrow_GrenadesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vEndPos = _vDestPos;
	m_fTime = 0.f;
	m_fDetail = 0.f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Grenade"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);
}

CDemonHunter_ClusterArrow_GrenadesEffect::~CDemonHunter_ClusterArrow_GrenadesEffect(void)
{
	Release();
}

void CDemonHunter_ClusterArrow_GrenadesEffect::Initialize()
{
	CEffect::Initialize();

	m_vStartPos = m_pTransformCom->m_vPos;
	m_vBezierPos = m_vStartPos;
	m_vBezierPos.y += 70.f;
}

int CDemonHunter_ClusterArrow_GrenadesEffect::Update()
{
	CEffect::Update();
	
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fDetail += (1.f / 30.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vPos = GetBezier(m_vStartPos, m_vBezierPos, m_vEndPos, m_fDetail);

	if(m_fDetail >= 1.f)
	{
		CDemonHunter_ClusterArrow_BombEffect* pBombEffect = new CDemonHunter_ClusterArrow_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
		pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
		pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
		pBombEffect->Initialize();

		
		pBombEffect = new CDemonHunter_ClusterArrow_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
		pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
		pBombEffect->Initialize();

		Destroy();
	}

	return 0;
}

void CDemonHunter_ClusterArrow_GrenadesEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_ClusterArrow_GrenadesEffect::Release()
{

}

D3DXVECTOR3 CDemonHunter_ClusterArrow_GrenadesEffect::GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail)
{
	D3DXVECTOR3 vResult = D3DXVECTOR3(0.f, 0.f, 0.f);

	vResult.x = _v3.x * (_fDetail * _fDetail) + _v2.x * (2 * _fDetail * (1 - _fDetail)) + _v1.x * ((1 - _fDetail) * (1 - _fDetail));
	vResult.y = _v3.y * (_fDetail * _fDetail) + _v2.y * (2 * _fDetail * (1 - _fDetail)) + _v1.y * ((1 - _fDetail) * (1 - _fDetail));
	vResult.z = _v3.z * (_fDetail * _fDetail) + _v2.z * (2 * _fDetail * (1 - _fDetail)) + _v1.z * ((1 - _fDetail) * (1 - _fDetail));

	return vResult;
}