#include "StdAfx.h"
#include "DemonHunter_ClusterArrow_ArrowEffect.h"

CDemonHunter_ClusterArrow_ArrowEffect::CDemonHunter_ClusterArrow_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDest)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDest = (*_pDest);

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Cluster_Arrow"));
	AddComponent(pMaterialCom);

	m_pTrailEffect = NULL;

	m_fTime = 0.f;
}

CDemonHunter_ClusterArrow_ArrowEffect::~CDemonHunter_ClusterArrow_ArrowEffect(void)
{
	Release();
}

void CDemonHunter_ClusterArrow_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(20.f, 100.f, 1.f);

	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	
	D3DXVECTOR3 vDir = m_vDest - m_pTransformCom->m_vPos;
	D3DXVECTOR3 vNewDir(vDir.x, 0.f, vDir.z);

	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vNewDir, &vNewDir);

	float fAngle = D3DXVec3Dot(&vDir, &vNewDir);
	fAngle = acosf(fAngle);

	m_pTransformCom->m_vAngle.x -= fAngle;

	m_pTransformCom->Update();

	m_pTrailEffect = new CDemonHunter_ClusterArrow_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld, vDir);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	m_vDir = vDir * 2000.f;

	m_iTest = 0;
}

int CDemonHunter_ClusterArrow_ArrowEffect::Update()
{
	CEffect::Update();

	D3DXVECTOR3 vDir = m_vDest - m_pTransformCom->m_vPos;
	float fDist = D3DXVec3Length(&vDir);

	if(fDist <= 5.f)
	{
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

		++m_iTest;

		if(m_iTest == 1)
		{
			CDemonHunter_ClusterArrow_BombEffect* pBombEffect = new CDemonHunter_ClusterArrow_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos;
			pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 1.f);
			pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
			pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
			pBombEffect->Initialize();

			pBombEffect = new CDemonHunter_ClusterArrow_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

			pTransformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos;
			pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 1.f);
			pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
			pBombEffect->Initialize();

			for(int i = 0; i < 3; ++i)
			{
				D3DXMATRIX matRotY;
				D3DXVECTOR3 vDir = D3DXVECTOR3(1.f, 1.f, 0.f);
				int iRand = rand() % 360;
				D3DXMatrixRotationY(&matRotY, D3DXToRadian(iRand));
				D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

				D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + vDir * 30.f;

				CDemonHunter_ClusterArrow_GrenadesEffect* pGrenadesEffect = new CDemonHunter_ClusterArrow_GrenadesEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDestPos);
				m_pLayer->AddObject(pGrenadesEffect, LAYER_TYPE_EFFECT);

				CTransformCom* pTransformCom = (CTransformCom*)pGrenadesEffect->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pGrenadesEffect->Initialize();
			}
		}

		if(m_fTime >= 0.5f)
		{
			Destroy();			
		}		
	}
	else
	{
		m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
	}

	return 0;
}

void CDemonHunter_ClusterArrow_ArrowEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_ClusterArrow_ArrowEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}