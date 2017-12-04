#include "StdAfx.h"
#include "DemonHunter_RainofVengeance_DecalEffect.h"

CDemonHunter_RainOfVengeance_DecalEffect::CDemonHunter_RainOfVengeance_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4; //데칼
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_RainOfVengeance_Decal"));
	AddComponent(pMaterialCom);

	m_iMode = 0;

	m_fAccTime = 0.f;
	m_fTime = 0.f;
}

CDemonHunter_RainOfVengeance_DecalEffect::~CDemonHunter_RainOfVengeance_DecalEffect(void)
{
	Release();
}

void CDemonHunter_RainOfVengeance_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(700.f, 700.f, 700.f);
}

int CDemonHunter_RainOfVengeance_DecalEffect::Update()
{
	CEffect::Update();

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

void CDemonHunter_RainOfVengeance_DecalEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_RainOfVengeance_DecalEffect::Release()
{
	
}

void CDemonHunter_RainOfVengeance_DecalEffect::Mode1()
{
	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += fTime;
	m_fAccTime += fTime;
	
	if(m_fTime >= 0.1f)
	{
		m_fTime = (rand() % 10) / 100.f;

		int iRand = (rand() % 5) + 5;

		for(int i = 0; i < iRand; ++i)
		{
			//기존에 구하던 방식 여러개의 지점에서 발사..
			
			int iPosX = (rand() % 450) - 225;
			int iPosZ = (rand() % 450) - 225;

			int iDestX = (rand() % 150) - 75;
			//int iDestZ = (rand() % 150) - 75;

			D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + D3DXVECTOR3((float)iPosX, 500.f, (float)iPosZ);
			D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + D3DXVECTOR3(float(iPosX + iDestX), 0.f, (float)iPosZ);
			D3DXVECTOR3 vDir = vDestPos - vPos;
			D3DXVec3Normalize(&vDir, &vDir);
						
			//하나의 지점에서 발사.
			float fAngle = D3DXVec3Dot(&vDir, &D3DXVECTOR3(0.f, -1.f, 0.f));
			float fDotX = D3DXVec3Dot(&vDir, &D3DXVECTOR3(1.f, 0.f, 0.f));

			if(fDotX >= 0)
				fAngle = D3DXToRadian(90.f) + acosf(fAngle);
			else
				fAngle = D3DXToRadian(90.f) - acosf(fAngle);

			//Effect
			CDemonHunter_RainOfVengeance_ArrowEffect* pEffect = new CDemonHunter_RainOfVengeance_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
			m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

			//Trasnform
			CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = vPos;
			pTransformCom->m_vAngle.z = fAngle;

			pEffect->Initialize();
			pEffect->AddCCollision();
		}
	}

	if(m_fAccTime >= 10.f)
	{
		++m_iMode;
	}
}

void CDemonHunter_RainOfVengeance_DecalEffect::Mode2()
{
	Destroy();
}