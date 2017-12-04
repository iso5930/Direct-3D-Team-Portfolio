#include "StdAfx.h"
#include "Monk_SevenSidedStrike_FlashEffect.h"

CMonk_SevenSidedStrike_FlashEffect::CMonk_SevenSidedStrike_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SevenSidedStrike_Flash"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 9;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 8.11f;
}

CMonk_SevenSidedStrike_FlashEffect::~CMonk_SevenSidedStrike_FlashEffect(void)
{
	Release();
}

void CMonk_SevenSidedStrike_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(5.f, 5.f, 5.f);
}

int CMonk_SevenSidedStrike_FlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.25f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_SevenSidedStrike_FlashEffect::Render()
{
	CEffect::Render();
}

void CMonk_SevenSidedStrike_FlashEffect::Release()
{

}