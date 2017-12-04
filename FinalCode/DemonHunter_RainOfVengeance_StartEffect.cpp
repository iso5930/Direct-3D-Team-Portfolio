#include "StdAfx.h"
#include "DemonHunter_RainOfVengeance_StartEffect.h"

CDemonHunter_RainOfVengeance_StartEffect::CDemonHunter_RainOfVengeance_StartEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDecalPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
	m_fAccTime = 0.0f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_vDecalPos = *_pDecalPos;
}

CDemonHunter_RainOfVengeance_StartEffect::~CDemonHunter_RainOfVengeance_StartEffect(void)
{
	Release();
}

void CDemonHunter_RainOfVengeance_StartEffect::Initialize()
{
	CEffect::Initialize();

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("RAIN_OF_VENGEANCE1.ogg"));

}

int CDemonHunter_RainOfVengeance_StartEffect::Update()
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
	}

	return 0;
}

void CDemonHunter_RainOfVengeance_StartEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_RainOfVengeance_StartEffect::Release()
{
	
}

void CDemonHunter_RainOfVengeance_StartEffect::Mode0()
{
	// 积己秦具登绰单,

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();


	m_fTime += fTime;
	m_fAccTime += fTime;

	if(m_fTime > 0.1f)
	{
		m_fTime = (rand() % 10) / 100.f;

		int iRand = (rand() % 5) + 4;

		for(int i = 0; i < iRand; ++i)
		{
			int iX = (rand() % 100) - 50;
			//int iZ = (rand() % 100) - 50;
			D3DXVECTOR3 vGoal = m_pTransformCom->m_vPos + D3DXVECTOR3((float)iX, 200.f, 0.f);
			D3DXVECTOR3 vDir = vGoal - m_pTransformCom->m_vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			//Angle
			float fAngle = D3DXVec3Dot(&vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
			float fDotX = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1.f, 0.f, 0.f));

			if(fDotX >= 0)
				fAngle = D3DXToRadian(-90.f) - acosf(fAngle);
			else
				fAngle = D3DXToRadian(-90.f) + acosf(fAngle);

			//Effect
			CDemonHunter_RainOfVengeance_ArrowEffect* pEffect = new CDemonHunter_RainOfVengeance_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
			m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

			//Trasnform
			CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos;
			pTransformCom->m_vAngle.z = fAngle;

			pEffect->Initialize();
		}
	}

	if(m_fAccTime >= 0.5f)
	{
		++m_iMode;
	}
}

void CDemonHunter_RainOfVengeance_StartEffect::Mode1()
{
	// Destroy
	Destroy();
	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("RAIN_OF_VENGEANCE2.ogg"));

	CDemonHunter_RainOfVengeance_DecalEffect* pDecalEffect = new CDemonHunter_RainOfVengeance_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_vDecalPos;

	pDecalEffect->Initialize();
}