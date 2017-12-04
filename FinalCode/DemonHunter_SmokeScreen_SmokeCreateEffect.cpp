#include "StdAfx.h"
#include "DemonHunter_SmokeScreen_SmokeCreateEffect.h"

CDemonHunter_SmokeScreen_SmokeCreateEffect::CDemonHunter_SmokeScreen_SmokeCreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;
}

CDemonHunter_SmokeScreen_SmokeCreateEffect::~CDemonHunter_SmokeScreen_SmokeCreateEffect(void)
{
	Release();
}

void CDemonHunter_SmokeScreen_SmokeCreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_SmokeScreen_SmokeCreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 1.f)
		Destroy();

	if(m_fTime >= 0.3f)
	{
		m_fTime = -100.f;

		int iRand = rand() % 30;

		CDemonHunter_SmokeScreen_SmokeEffect* pSmokeEffect = new CDemonHunter_SmokeScreen_SmokeEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pSmokeEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pSmokeEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.f, (float)iRand, 0.f);
		pSmokeEffect->Initialize();
	}

	return 0;
}

void CDemonHunter_SmokeScreen_SmokeCreateEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SmokeScreen_SmokeCreateEffect::Release()
{

}
