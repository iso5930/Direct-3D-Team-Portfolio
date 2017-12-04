#include "StdAfx.h"
#include "Wizard_RayOfFrost_HitEffect.h"

CWizard_RayOfFrost_HitEffect::CWizard_RayOfFrost_HitEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CParticleEffect(_tszObjKey, _eObjType, _pOwner, 3000, 500, _T("Effect_Snow"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 18;
	AddComponent(pRenderCom);
	
	m_fCreateTime = 0.f;

	m_bDeath = false;
}

CWizard_RayOfFrost_HitEffect::~CWizard_RayOfFrost_HitEffect(void)
{
	//Release();
}

void CWizard_RayOfFrost_HitEffect::Initialize()
{
	CParticleEffect::Initialize();
}

int CWizard_RayOfFrost_HitEffect::Update()
{
	CParticleEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();
	m_fCreateTime += fTime;
	
	//float fTime = CTimeMgr::GetInstance()->GetDeltaTime();
	//m_fCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();
	//
	//for(DWORD i = 0; i < m_dwCount; ++i)
	//{
	//	m_pParticleValue[i].fAccTime += fTime;
	//	m_pParticleValue[i].vPos += m_pParticleValue[i].vVelocity * fTime;
	//	/*
	//	m_pParticleValue[i].vPos.x += m_pParticleValue[i].vVelocity.x * fTime * 1000.f;	
	//	m_pParticleValue[i].vPos.y += m_pParticleValue[i].vVelocity.y * fTime - 0.5f * 9.8f * fTime * fTime * 1000.f;
	//	m_pParticleValue[i].vPos.z += m_pParticleValue[i].vVelocity.z * fTime * 1000.f;
	//	*/
	//	
	//	if(m_pParticleValue[i].fAccTime >= 1.f)
	//	{
	//		Release_Particle(i);
	//	}

	//	m_pVS[i].vPos = m_pParticleValue[i].vPos;
	//	m_pVS[i].fSize = m_pParticleValue[i].fSize;
	//}

	//if(m_bDeath == true)
	//{
	//	if(m_dwCount == 0)
	//	{
	//		Destroy();
	//	}
	//}
	//else if(m_fCreateTime >= 0.01f)
	//{
	//	m_fCreateTime = 0.f;

	//	for(int i = 0; i < 200; ++i)
	//	{
	//		ParticleValue tParticleValue;
	//		ZeroMemory(&tParticleValue, sizeof(ParticleValue));

	//		tParticleValue.bAlive = true;

	//		float fThata = float(rand() % 61) - 30.f;
	//		float fPhi = float(rand() % 360);
	//		float fSpeed = (10.f + float(rand() % 81)) * 0.03f;

	//		fThata = D3DXToRadian(fThata);
	//		fPhi = D3DXToRadian(fPhi);

	//		tParticleValue.vVelocity.x = fSpeed * sinf(fThata) * sinf(fPhi);
	//		tParticleValue.vVelocity.y = fSpeed * cosf(fThata);
	//		tParticleValue.vVelocity.z = fSpeed * sinf(fThata) * cosf(fPhi);
	//		
	//		tParticleValue.vPos = m_pTransformCom->m_vPos + 20.f * D3DXVECTOR3(cosf(fPhi), 0.f, sinf((fPhi)));
	//
	//		/*
	//		tParticleValue.vVelocity.x = 0.5f * (((rand() % 101) * 0.01f) - 0.4f);
	//		tParticleValue.vVelocity.y = -1 - 1 * ((rand() % 101) * 0.01f);
	//		tParticleValue.vVelocity.z = 2 * (((rand() % 101) * 0.01f) - 0.4f);
	//		*/
	//		/*
	//		tParticleValue.vVelocity.x = (((float) rand())/((float)RAND_MAX) - 0.5f) * 0.5f;
	//		tParticleValue.vVelocity.y = 4.f * (((float) rand())/((float)RAND_MAX)) / 10.f+1.f;
	//		tParticleValue.vVelocity.z = (((float) rand())/((float)RAND_MAX) - 0.5f) * 0.5f;
	//		*/
	//		tParticleValue.fSize = 300.f;
	//		
	//		if(Add_Particle(tParticleValue) == -1)
	//			break;
	//	}
	//}

	if(m_bDeath)
	{
		if(m_dwCount == 0)
			Destroy();
	}
	else if(m_fCreateTime >= 0.01f)
	{
		m_fCreateTime = 0.f;

		for(int i = 0; i < 50; ++i)
		{
			ParticleValue tParticleValue;
			ZeroMemory(&tParticleValue, sizeof(ParticleValue));

			tParticleValue.bAlive = true;
			tParticleValue.vPos = m_pTransformCom->m_vPos;
			tParticleValue.vVelocity.x = 2 * (((rand() % 101) * 0.01f) - 0.5f);
			tParticleValue.vVelocity.y = 2 * (((rand() % 101) * 0.01f) - 0.5f);
			tParticleValue.vVelocity.z = 2 * (((rand() % 101) * 0.01f) - 0.5f);
			if(Add_Particle(tParticleValue) == -1)
			{
				break;
			}
		}
	}

	for(DWORD i = 0; i < m_dwCount; ++i)
	{
		m_pParticleValue[i].fAccTime += fTime;
		m_pParticleValue[i].vPos += m_pParticleValue[i].vVelocity * 1000.f * fTime;

		if(m_pParticleValue[i].fAccTime >= 0.1f)
			Release_Particle(i);

		m_pVS[i].vPos = m_pParticleValue[i].vPos;
		m_pVS[i].fSize = m_pParticleValue[i].fSize;
	}

	return 0;
}

void CWizard_RayOfFrost_HitEffect::Render()
{
	CParticleEffect::Render();
}

void CWizard_RayOfFrost_HitEffect::Release()
{
	m_bDeath = true;
	m_fCreateTime = 0.f;
}