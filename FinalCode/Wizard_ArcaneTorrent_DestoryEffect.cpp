#include "StdAfx.h"
#include "Wizard_ArcaneTorrent_DestoryEffect.h"

CWizard_ArcaneTorrent_DestoryEffect::CWizard_ArcaneTorrent_DestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_ArcaneTorrent_DestoryEffect"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f));
	AddComponent(pCollisionCom);

	// MaxCnt
	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 4.0f;
}

CWizard_ArcaneTorrent_DestoryEffect::~CWizard_ArcaneTorrent_DestoryEffect(void)
{
	Release();
}

void CWizard_ArcaneTorrent_DestoryEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CWizard_ArcaneTorrent_DestoryEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.y += D3DXToRadian(720.f) * 10.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 600.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAlpha += 10.f * CTimeMgr::GetInstance()->GetDeltaTime();

 	if(m_fTime >= 0.1f)
 	{
 		Destroy();
 	}

	return 0;
}

void CWizard_ArcaneTorrent_DestoryEffect::Render()
{
	CEffect::Render();
}

void CWizard_ArcaneTorrent_DestoryEffect::Release()
{

}