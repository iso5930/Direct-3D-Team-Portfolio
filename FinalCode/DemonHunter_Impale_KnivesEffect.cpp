#include "StdAfx.h"
#include "DemonHunter_Impale_KnivesEffect.h"

CDemonHunter_Impale_KnivesEffect::CDemonHunter_Impale_KnivesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Impale"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	D3DXVec3Cross(&m_vAxis, &m_vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_fAngle = 0.f;
	m_fTime = 0.f;

	m_pTrailEffect = NULL;

	m_fAccTime = 0.f;

	// Coef
	m_fCoef = 7.5f;
}

CDemonHunter_Impale_KnivesEffect::~CDemonHunter_Impale_KnivesEffect(void)
{
	Release();
}

void CDemonHunter_Impale_KnivesEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CDemonHunter_Impale_KnivesTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();
}

int CDemonHunter_Impale_KnivesEffect::Update()
{
	CEffect::Update();
	
	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.f) == false)
	{
		Destroy();
	}

	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 1.f)
	{
		Destroy();
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();	
	m_fAngle += D3DXToRadian(720.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.05f)
	{
		m_fTime = 0.f;

		//ÀÜ»ó »ý¼º...
		CDemonHunter_Impale_AfterImageEffect* pAfterImage = new CDemonHunter_Impale_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, m_vAxis, m_fAngle);
		m_pLayer->AddObject(pAfterImage, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterImage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y - D3DXToRadian(90.f);
		
		pAfterImage->Initialize();
	}

	D3DXMATRIX matScale, matRotate, matAxis, matTrans;
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	MatrixRotation(&matRotate, m_pTransformCom->m_vAngle.x, m_pTransformCom->m_vAngle.y, m_pTransformCom->m_vAngle.z);
	D3DXMatrixRotationAxis(&matAxis, &m_vAxis, m_fAngle);

	m_pTransformCom->m_mWorld = matScale * matRotate * matAxis * matTrans;

	return 0;
}

void CDemonHunter_Impale_KnivesEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Impale_KnivesEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}