#include "StdAfx.h"
#include "DemonHunter_Bola_ArrowEffect.h"

CDemonHunter_Bola_ArrowEffect::CDemonHunter_Bola_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = (*_pDir);
	m_fTime = 0.f;
	m_fAccTime = 0.f;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Bola_Arrow"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 1.6f;
}

CDemonHunter_Bola_ArrowEffect::~CDemonHunter_Bola_ArrowEffect(void)
{
	Release();
}

void CDemonHunter_Bola_ArrowEffect::Initialize()
{
	CEffect::Initialize();
	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CDemonHunter_Bola_ArrowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 1.f)
	{
		Destroy();
	}

	if(m_fTime >= 0.15f)
	{
		m_fTime = 0.f;

		CDemonHunter_Bola_AfterImageEffect* pEffect = new CDemonHunter_Bola_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pEffect);

		CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pEffect->Initialize();
	}

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.f) == false)
	{
		Destroy();
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.y += D3DXToRadian(720.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CDemonHunter_Bola_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Bola_ArrowEffect::Release()
{

}