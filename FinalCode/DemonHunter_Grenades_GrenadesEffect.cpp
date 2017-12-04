#include "StdAfx.h"
#include "DemonHunter_Grenades_GrenadesEffect.h"

CDemonHunter_Grenades_GrenadesEffect::CDemonHunter_Grenades_GrenadesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
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

	m_fDetail = 0.f;
	m_iCount = 0;
	m_vDestPos = _vDestPos;
}

CDemonHunter_Grenades_GrenadesEffect::~CDemonHunter_Grenades_GrenadesEffect(void)
{
	Release();
}

void CDemonHunter_Grenades_GrenadesEffect::Initialize()
{
	CEffect::Initialize();

	m_vStartPos = m_pTransformCom->m_vPos;
	
	D3DXVECTOR3 vDir = m_vDestPos - D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_vDestPos.y, m_pTransformCom->m_vPos.z);
	float		fLength = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVECTOR3 vDestPos = D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_vDestPos.y, m_pTransformCom->m_vPos.z) + vDir * (fLength * 0.7f);
	m_vEndPos = vDestPos;

	vDir = D3DXVECTOR3(m_vEndPos.x, m_vStartPos.y, m_vEndPos.z) - m_vStartPos;
	fLength = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	m_vPos = m_vStartPos + vDir * (fLength * 0.5f);
	m_vPos.y += 50.f;
}

int CDemonHunter_Grenades_GrenadesEffect::Update()
{
	CEffect::Update();

	m_fDetail += (1.f / 30.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vPos = GetBezier(m_vStartPos, m_vPos, m_vEndPos, m_fDetail);
	m_pTransformCom->m_vAngle.x += D3DXToRadian(720.f) * 10.f *  CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.y -= D3DXToRadian(520.f) * 15.f *  CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.z += D3DXToRadian(360.f) * 20.f *  CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fDetail >= 1.f)
	{
		m_fDetail = 0.f;
		++m_iCount;

		switch(m_iCount)
		{
		case 1:
			Mode1();
			break;

		case 2:
			Mode2();
			break;

		case 3:
			Mode3();
			break;
		}
	}

	return 0;
}

void CDemonHunter_Grenades_GrenadesEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Grenades_GrenadesEffect::Release()
{

}

void CDemonHunter_Grenades_GrenadesEffect::Mode1()
{
	m_vStartPos = m_pTransformCom->m_vPos;

	D3DXVECTOR3 vDir = m_vDestPos - D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_vDestPos.y, m_pTransformCom->m_vPos.z);
	float		fLength = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVECTOR3 vDestPos = D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_vDestPos.y, m_pTransformCom->m_vPos.z) + vDir * (fLength * 0.6f);
	m_vEndPos = vDestPos;

	vDir = D3DXVECTOR3(m_vEndPos.x, m_vStartPos.y, m_vEndPos.z) - m_vStartPos;
	fLength = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	m_vPos = m_vStartPos + vDir * (fLength * 0.5f);
	m_vPos.y += 30.f;
}

void CDemonHunter_Grenades_GrenadesEffect::Mode2()
{
	m_vStartPos = m_pTransformCom->m_vPos;
	m_vEndPos = m_vDestPos;

	D3DXVECTOR3 vDir = D3DXVECTOR3(m_vEndPos.x, m_vStartPos.y, m_vEndPos.z) - m_vStartPos;
	float fLength = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	m_vPos = m_vStartPos + vDir * (fLength * 0.5f);
	m_vPos.y += 30.f;
}

void CDemonHunter_Grenades_GrenadesEffect::Mode3()
{
	Destroy();

	CDemonHunter_Grenades_BombEffect* pBombEffect = new CDemonHunter_Grenades_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pBombEffect->Initialize();

	CDemonHunter_Grenades_DustEffect* pDustEffect = new CDemonHunter_Grenades_DustEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pDustEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pDustEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDustEffect->Initialize();

	CDemonHunter_Grenades_DecalEffect* pDecalEffect = new CDemonHunter_Grenades_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalEffect->Initialize();
}

D3DXVECTOR3 CDemonHunter_Grenades_GrenadesEffect::GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail)
{
	D3DXVECTOR3 vResult = D3DXVECTOR3(0.f, 0.f, 0.f);
	
	vResult.x = _v3.x * (_fDetail * _fDetail) + _v2.x * (2 * _fDetail * (1 - _fDetail)) + _v1.x * ((1 - _fDetail) * (1 - _fDetail));
	vResult.y = _v3.y * (_fDetail * _fDetail) + _v2.y * (2 * _fDetail * (1 - _fDetail)) + _v1.y * ((1 - _fDetail) * (1 - _fDetail));
	vResult.z = _v3.z * (_fDetail * _fDetail) + _v2.z * (2 * _fDetail * (1 - _fDetail)) + _v1.z * ((1 - _fDetail) * (1 - _fDetail));

	return vResult;
}