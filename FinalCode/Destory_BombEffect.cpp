#include "StdAfx.h"
#include "Destory_BombEffect.h"

CDestory_BombEffect::CDestory_BombEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _tszName)
:CParticleEffect(_tszObjKey, _eObjType, _pOwner, 1000, 500, _tszName)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 18;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
	m_bDeath = false;
	m_fCreateTime = 0.f;
}

CDestory_BombEffect::~CDestory_BombEffect(void)
{
	
}

void CDestory_BombEffect::Initialize()
{
	CParticleEffect::Initialize();
}
	
int CDestory_BombEffect::Update()
{	
	CParticleEffect::Update();
	
	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();
	m_fTime += fTime;
	m_fCreateTime += fTime;

	if(m_fTime >= 0.1f)
		m_bDeath = true;

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

void CDestory_BombEffect::Render()
{
	CParticleEffect::Render();
}

void CDestory_BombEffect::Release()
{

}