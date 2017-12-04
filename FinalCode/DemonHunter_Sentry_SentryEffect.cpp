#include "StdAfx.h"
#include "DemonHunter_Sentry_SentryEffect.h"

CDemonHunter_Sentry_SentryEffect::CDemonHunter_Sentry_SentryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Sentry"));
	m_pMesh = (CDynamicMesh*)(pBufferCom->m_BufferVec[0]);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 16;
	AddComponent(pRenderCom);

	m_iMode = 0;
	m_fTime = 0.f;
	m_fAccTime = 0.f;

	m_pBaseEffect = NULL;

	m_bCheck = false;
}

CDemonHunter_Sentry_SentryEffect::~CDemonHunter_Sentry_SentryEffect(void)
{
	Release();
}

void CDemonHunter_Sentry_SentryEffect::Initialize()
{
	CEffect::Initialize();

	m_pMesh->m_pAnimController->SetAnimation(0);

	m_pBaseEffect = new CDemonHunter_Sentry_BaseEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pOwner->GetLayer()->AddObject(m_pBaseEffect, LAYER_TYPE_EFFECT);
	m_pBaseEffect->Initialize();
}

int CDemonHunter_Sentry_SentryEffect::Update()
{
	CEffect::Update();

	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 15.f && m_bCheck == false)
	{
		m_bCheck = true;
		m_pMesh->m_pAnimController->SetAnimation(3);
		m_pMesh->m_pAnimController->SetTrackPos(0.0);
		m_iMode = 4;
	}

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;

	case 2:
		Mode3();
		break;

	case 3:
		Mode4();
		break;

	case 4:
		Mode5();
		break;
	}

	return 0;
}

void CDemonHunter_Sentry_SentryEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Sentry_SentryEffect::Release()
{
	if(m_pBaseEffect != NULL)
	{
		m_pBaseEffect->Destroy();
		m_pBaseEffect = NULL;
	}
}

void CDemonHunter_Sentry_SentryEffect::Mode1()
{
	if(m_pMesh->m_pAnimController->m_dFrameTime - 0.2 <= m_pMesh->m_pAnimController->GetTrackPos())
	{
		m_pMesh->m_pAnimController->SetAnimation(1);
		m_pMesh->m_pAnimController->SetTrackPos(0.0);

		++m_iMode;
	}
}

void CDemonHunter_Sentry_SentryEffect::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.4f)
	{
		m_fTime = 0.f;

		m_iMode = 2;
	}
}

void CDemonHunter_Sentry_SentryEffect::Mode3()
{
	m_iMode = 0;

	//АјАн
	float fMin = 800.f;
	int	 iFindMonster = -1;
	CTransformCom* pFindMonster;

	m_vecMonster.clear();

	m_pLayer->FindObjects(m_vecMonster, _T("Monster"), LAYER_TYPE_MONSTER);

	for(size_t i = 0; i < m_vecMonster.size(); ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_vecMonster[i]->GetComponent(COM_TYPE_TRANSFORM);

		D3DXVECTOR3 vLength = pTransformCom->m_vPos - m_pTransformCom->m_vPos;
		float fDist = D3DXVec3Length(&vLength);

		if(fDist <= fMin)
		{
			fMin = fDist;
			iFindMonster = i;
			pFindMonster = pTransformCom;
		}
	}

	if(iFindMonster == -1)
		return;

	m_iMode = 3;
	m_pMesh->m_pAnimController->SetAnimation(2);
	m_pMesh->m_pAnimController->SetTrackPos(0.0);

	D3DXVECTOR3 vDir = pFindMonster->m_vPos - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

	CDemonHunter_Sentry_ArrowEffect* pArrowEffect = new CDemonHunter_Sentry_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 700.f));
	m_pLayer->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();
}

void CDemonHunter_Sentry_SentryEffect::Mode4()
{
	if(m_pMesh->m_pAnimController->GetFrameTime() - 0.2 <= m_pMesh->m_pAnimController->GetTrackPos())
	{
		m_pMesh->m_pAnimController->SetAnimation(1);
		m_pMesh->m_pAnimController->SetTrackPos(0.0);
		m_iMode = 1; 
	}
}

void CDemonHunter_Sentry_SentryEffect::Mode5()
{
	if(m_pMesh->m_pAnimController->GetFrameTime() - 0.2 <= m_pMesh->m_pAnimController->GetTrackPos())
	{
		Destroy();
	}
}

void CDemonHunter_Sentry_SentryEffect::SentryDestory()
{
	m_bCheck = true;
	m_pMesh->m_pAnimController->SetAnimation(3);
	m_pMesh->m_pAnimController->SetTrackPos(0.0);
	m_iMode = 4;
}