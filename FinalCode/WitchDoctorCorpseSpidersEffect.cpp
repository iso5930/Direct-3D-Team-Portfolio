#include "StdAfx.h"
#include "WitchDoctorCorpseSpidersEffect.h"

CWitchDoctorCorpseSpidersEffect::CWitchDoctorCorpseSpidersEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_CorpseSpider_Jar"));
	m_pDynamicMesh = ((CDynamicMesh*)(pBufferCom->m_BufferVec[0]));
	m_pDynamicMesh->m_pAnimController->SetAnimation(0);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 16;
	AddComponent(pRenderCom);

	m_fDetail = 0.f;
	m_iMode = 0;
	m_vEndPos = _vDestPos;
	

}

CWitchDoctorCorpseSpidersEffect::~CWitchDoctorCorpseSpidersEffect(void)
{
	Release();
}

void CWitchDoctorCorpseSpidersEffect::Initialize()
{
	CEffect::Initialize();

	m_vStartPos = m_pTransformCom->m_vPos;
	D3DXVECTOR3 vPos = ((m_vEndPos - m_vStartPos) / 3);

	vPos.y =0.f;
	m_vPos	= m_vStartPos + vPos;
	m_vPos.y = max(m_vEndPos.y , m_vStartPos.y) + 200.f;

}

int CWitchDoctorCorpseSpidersEffect::Update()
{

	CEffect::Update();
	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;

	}


	return 0;
}

void CWitchDoctorCorpseSpidersEffect::Render()
{
	CEffect::Render();
}

void CWitchDoctorCorpseSpidersEffect::Release()
{

}

void CWitchDoctorCorpseSpidersEffect::Mode0()
{
	if(m_fDetail <=  1.f)
	{
		m_fDetail += CTimeMgr::GetInstance()->GetDeltaTime() * 1.5f ;
		m_pTransformCom->m_vPos = GetBezier(m_vStartPos, m_vPos, m_vEndPos, m_fDetail);
	}
	else
	{
		m_fDetail = 1.f;
		m_iMode = 1;
		m_pDynamicMesh->m_pAnimController->SetAnimation(1);		
	}
	int iRotNum =  2;				
	float fRadian = -(360.f * iRotNum * m_fDetail);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(fRadian);  


}

void CWitchDoctorCorpseSpidersEffect::Mode1()
{
	CWitchDoctorCorpseSpiders_SpiderEffect* pCorpseSpiders_SpiderEffect = NULL;
	CTransformCom* pTransformCom = NULL;

	pCorpseSpiders_SpiderEffect	= new CWitchDoctorCorpseSpiders_SpiderEffect(NULL , OBJ_TYPE_DYNAMIC , m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCorpseSpiders_SpiderEffect, LAYER_TYPE_EFFECT);
	pTransformCom = (CTransformCom*)pCorpseSpiders_SpiderEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vPos.x += 50.f;
	pCorpseSpiders_SpiderEffect->Initialize();

	pCorpseSpiders_SpiderEffect = new CWitchDoctorCorpseSpiders_SpiderEffect(NULL , OBJ_TYPE_DYNAMIC , m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCorpseSpiders_SpiderEffect, LAYER_TYPE_EFFECT);
	pTransformCom = (CTransformCom*)pCorpseSpiders_SpiderEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vPos.z += 50.f;
	pCorpseSpiders_SpiderEffect->Initialize();


	pCorpseSpiders_SpiderEffect = new CWitchDoctorCorpseSpiders_SpiderEffect(NULL , OBJ_TYPE_DYNAMIC , m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCorpseSpiders_SpiderEffect, LAYER_TYPE_EFFECT);
	pTransformCom = (CTransformCom*)pCorpseSpiders_SpiderEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vPos.x += -50.f;
	pCorpseSpiders_SpiderEffect->Initialize();

	m_iMode = 2; 
}

void CWitchDoctorCorpseSpidersEffect::Mode2()
{
	if (m_pDynamicMesh->m_pAnimController->m_dFrameTime - 0.1 <= m_pDynamicMesh->m_pAnimController->GetTrackPos())
	{
		m_pDynamicMesh->m_iMode = 2;

		Destroy();
	}


}

D3DXVECTOR3 CWitchDoctorCorpseSpidersEffect::GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail)
{
	D3DXVECTOR3 vResult = D3DXVECTOR3(0.f, 0.f, 0.f);
	
	vResult.x = _v3.x * (_fDetail * _fDetail) + _v2.x * (2 * _fDetail * (1 - _fDetail)) + _v1.x * ((1 - _fDetail) * (1 - _fDetail));
	vResult.y = _v3.y * (_fDetail * _fDetail) + _v2.y * (2 * _fDetail * (1 - _fDetail)) + _v1.y * ((1 - _fDetail) * (1 - _fDetail));
	vResult.z = _v3.z * (_fDetail * _fDetail) + _v2.z * (2 * _fDetail * (1 - _fDetail)) + _v1.z * ((1 - _fDetail) * (1 - _fDetail));

	return vResult;
}