#include "StdAfx.h"
#include "Wizard_MagicMissile_MissileEffect.h"

CWizard_MagicMissile_MissileEffect::CWizard_MagicMissile_MissileEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;

	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_MagicMissile0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_MagicMissile1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_MagicMissile2")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 2;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.01f;

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);

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

	m_pTrailEffect = NULL;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_fCoef = 2.3f;
}

CWizard_MagicMissile_MissileEffect::~CWizard_MagicMissile_MissileEffect(void)
{
	Release();
}

void CWizard_MagicMissile_MissileEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CWizard_MagicMissile_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mTrans);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);

	m_pTrailEffect->Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 150.f);
}

int CWizard_MagicMissile_MissileEffect::Update()
{
	CEffect::Update();

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.f;

		m_Frame.iCur = rand() % m_Frame.iEnd + 1;
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];	

	return 0; 
}

void CWizard_MagicMissile_MissileEffect::Render()
{
	CEffect::Render();
}	

void CWizard_MagicMissile_MissileEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}