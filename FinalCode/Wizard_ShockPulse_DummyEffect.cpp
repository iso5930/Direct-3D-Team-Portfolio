#include "StdAfx.h"
#include "Wizard_ShockPulse_DummyEffect.h"

CWizard_ShockPulse_DummyEffect::CWizard_ShockPulse_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_vDestPos = _vDestPos;

	m_iMode = 0;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 1.94f;
}

CWizard_ShockPulse_DummyEffect::~CWizard_ShockPulse_DummyEffect(void)
{
	Release();
}

void CWizard_ShockPulse_DummyEffect::Initialize()
{
	CEffect::Initialize();

	m_vDir = m_vDestPos - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	float fAngle = -D3DXToRadian(float(rand() % 10));
	D3DXMATRIX matRotY;
	D3DXMatrixRotationY(&matRotY, fAngle);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotY);

	m_vPoint = m_pTransformCom->m_vPos + m_vDir * float(rand() % (30 + 130));
}

int CWizard_ShockPulse_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vPos += m_vDir * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();

	D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - m_vPoint;
	float fLength = D3DXVec3Length(&vLength);

	if(m_fTime >= 0.05f)
	{
		m_fTime = 0.f;

		CWizard_ShockPulse_LightingEffect* pEffect = new CWizard_ShockPulse_LightingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pEffect->Initialize();
	}

	if(fLength <= 10.f)
	{
		switch(m_iMode)
		{
		case 0:
			Mode1();
			break;

		case 1:
			Mode2();
			break;

		case 2:
			Destroy();
			break;
		}
	}

	return 0;
}

void CWizard_ShockPulse_DummyEffect::Render()
{
	CEffect::Render();
}

void CWizard_ShockPulse_DummyEffect::Release()
{

}

void CWizard_ShockPulse_DummyEffect::Mode1()
{
	float fAngle = D3DXToRadian(float(rand() % 20) + 70.f);
	D3DXMATRIX matRotY;
	D3DXMatrixRotationY(&matRotY, fAngle);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRotY);

	m_vPoint = m_pTransformCom->m_vPos + m_vDir * float(rand() % (30 + 130));

	++m_iMode;
}

void CWizard_ShockPulse_DummyEffect::Mode2()
{
	m_vDir = m_vDestPos - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	m_vPoint = m_vDestPos;

	++m_iMode;
}