#include "StdAfx.h"
#include "Monk_MantraOfRetribution_CreateEffect.h"

CMonk_MantraOfRetribution_CreateEffect::CMonk_MantraOfRetribution_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CParticleEffect(_tszObjKey, _eObjType, _pOwner, 1000, 500, _T("Effect_MantraOfRetribution_Particle"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 18;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
	m_iMode = 0;
	m_fAccTime = 0.f;
}

CMonk_MantraOfRetribution_CreateEffect::~CMonk_MantraOfRetribution_CreateEffect(void)
{
	Release();
}

void CMonk_MantraOfRetribution_CreateEffect::Initialize()
{
	CParticleEffect::Initialize();
}

int CMonk_MantraOfRetribution_CreateEffect::Update()
{
	CParticleEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	for(DWORD i = 0; i < m_dwCount; ++i)
	{
		m_pParticleValue[i].fAccTime += fTime;
		m_pParticleValue[i].vPos += m_pParticleValue[i].vVelocity * fTime;

		if(m_pParticleValue[i].fAccTime >= 0.2f)
		{
			Release_Particle(i);
		}

		m_pVS[i].vPos = m_pParticleValue[i].vPos;
		m_pVS[i].fSize = m_pParticleValue[i].fSize;
	}

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

void CMonk_MantraOfRetribution_CreateEffect::Render()
{
	CParticleEffect::Render();
}

void CMonk_MantraOfRetribution_CreateEffect::Release()
{

}

void CMonk_MantraOfRetribution_CreateEffect::Mode1()
{
	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += fTime;
	m_fAccTime += fTime;

	if(m_fAccTime >= 0.2f)
	{
		++m_iMode;
	}

	if(m_fTime >= 0.01f)
	{
		m_fTime = 0.f;

		ParticleValue tParticleValue;
		ZeroMemory(&tParticleValue, sizeof(ParticleValue));

		int iRand = rand() % 360;
		D3DXVECTOR3 vDir;
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(float(iRand)));
		D3DXVec3TransformNormal(&vDir, &AXIS_X, &matRotY);
		CTransformCom* pTrnasformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
		tParticleValue.vPos = pTrnasformCom->m_vPos + D3DXVECTOR3(0.f, 80.f, 0.f);
		tParticleValue.vVelocity = vDir * 700.f;
		tParticleValue.fSize = 30.f;

		Add_Particle(tParticleValue);
	}
}

void CMonk_MantraOfRetribution_CreateEffect::Mode2()
{
	if(m_dwCount == 0)
	{
		Destroy();
	}
}