#include "StdAfx.h"
#include "Monk_FistsOfThunder_FlashEffect.h"

CMonk_FistsOfThunder_FlashEffect::CMonk_FistsOfThunder_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_FistsOfThunder_Flash"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
	
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 1.9f;
}

CMonk_FistsOfThunder_FlashEffect::~CMonk_FistsOfThunder_FlashEffect(void)
{
	Release();
}

void CMonk_FistsOfThunder_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(40.f, 40.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CMonk_FistsOfThunder_FlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

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

void CMonk_FistsOfThunder_FlashEffect::Render()
{
	CEffect::Render();
}

void CMonk_FistsOfThunder_FlashEffect::Release()
{

}

void CMonk_FistsOfThunder_FlashEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_FistsOfThunder_FlashEffect::Mode2()
{
	if(m_fTime >= 0.1f)
	{
		Destroy();
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}
