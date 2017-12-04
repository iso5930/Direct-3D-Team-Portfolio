#include "StdAfx.h"
#include "Wizard_Blizzard_IceCreateEffect.h"

CWizard_Blizzard_IceCreateEffect::CWizard_Blizzard_IceCreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;
	m_fCloudTime = 0.f;
}

CWizard_Blizzard_IceCreateEffect::~CWizard_Blizzard_IceCreateEffect(void)
{
	Release();
}

void CWizard_Blizzard_IceCreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_Blizzard_IceCreateEffect::Update()
{	
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fCloudTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fCloudTime >= 0.03f)
	{
		m_fCloudTime = 0.f;

		for(int i = 0; i < 3; ++i)
		{
			int iPosX = (rand() % 400) - 200;
			int iPosZ = (rand() % 400) - 200;

			int iDestX = (rand() % 150) - 75;
			float fSpeed = float(rand() % 200) + 800.f;

			D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + D3DXVECTOR3((float)iPosX, 500.f, (float)iPosZ);
			D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + D3DXVECTOR3(float(iPosX + iDestX), 0.f, (float)iPosZ);
			D3DXVECTOR3 vDir = vDestPos - vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			//하나의 지점에서 발사.
			float fAngle = D3DXVec3Dot(&vDir, &D3DXVECTOR3(0.f, -1.f, 0.f));
			float fDotX = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1.f, 0.f, 0.f));

			if(fDotX >= 0)
				fAngle = D3DXToRadian(-90.f) + acosf(fAngle);
			else
				fAngle = D3DXToRadian(-90.f) - acosf(fAngle);

			CWizard_Blizzard_CloudEffect* pCloud = new CWizard_Blizzard_CloudEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 500.f));
			m_pLayer->AddObject(pCloud, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pCloud->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = vPos;
			pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
			pCloud->Initialize();
		}
	}
	
	if(m_fTime >= 0.3f)
	{
		m_fTime = 0.f;

		for(int i = 0; i < 3; ++i)
		{
			//기존에 구하던 방식 여러개의 지점에서 발사..

			int iPosX = (rand() % 400) - 200;
			int iPosZ = (rand() % 400) - 200;

			int iDestX = (rand() % 150) - 75;
			float fSpeed = float(rand() % 200) + 800.f;
			
			D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + D3DXVECTOR3((float)iPosX, 500.f, (float)iPosZ);
			D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + D3DXVECTOR3(float(iPosX + iDestX), 0.f, (float)iPosZ);
			D3DXVECTOR3 vDir = vDestPos - vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			//하나의 지점에서 발사.
			float fAngle = D3DXVec3Dot(&vDir, &D3DXVECTOR3(0.f, -1.f, 0.f));
			float fDotX = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1.f, 0.f, 0.f));

			if(fDotX >= 0)
				fAngle = D3DXToRadian(-90.f) + acosf(fAngle);
			else
				fAngle = D3DXToRadian(-90.f) - acosf(fAngle);

			//Effect
			CWizard_Blizzard_IceEffect* pEffect = new CWizard_Blizzard_IceEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * fSpeed), vDestPos.y);
			m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

			//Trasnform
			CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = vPos;
			pTransformCom->m_vAngle.x = D3DXToRadian(-90.f);

			pEffect->Initialize();
		}
	}

	if(m_fAccTime >= 8.f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Blizzard_IceCreateEffect::Render()
{
	CEffect::Render();
}

void CWizard_Blizzard_IceCreateEffect::Release()
{

}
