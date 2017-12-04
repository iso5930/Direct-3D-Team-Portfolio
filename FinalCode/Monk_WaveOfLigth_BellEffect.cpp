#include "StdAfx.h"
#include "Monk_WaveOfLigth_BellEffect.h"

CMonk_WaveOfLigth_BellEffect::CMonk_WaveOfLigth_BellEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WaveOfLight"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 14;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;
	m_iMode = 0;
	m_fAlpha = 0.5f;

	// Coef
	m_fCoef = 2.0f;
}

CMonk_WaveOfLigth_BellEffect::~CMonk_WaveOfLigth_BellEffect(void)
{
	Release();
}

void CMonk_WaveOfLigth_BellEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vPos.y += 200.f;
}

int CMonk_WaveOfLigth_BellEffect::Update()
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

void CMonk_WaveOfLigth_BellEffect::Render()
{
	CEffect::Render();
}

void CMonk_WaveOfLigth_BellEffect::Release()
{

}

void CMonk_WaveOfLigth_BellEffect::Mode1()
{	
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;

		CMonk_WaveOfLight_WaveEffect* pWaveEffect = new CMonk_WaveOfLight_WaveEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pWaveEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWaveEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pWaveEffect->Initialize();
	}

	m_pTransformCom->m_vPos += D3DXVECTOR3(0.f, -1.f, 0.f) * 2000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_WaveOfLigth_BellEffect::Mode2()
{
	if(m_fTime >= 1.f)
	{
		Destroy();

		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("WAVE_OF_LIGHT2.ogg"));

		CMonk_WaveOfLigth_BellDestoryEffect* pDestoryEffect = new CMonk_WaveOfLigth_BellDestoryEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDestoryEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDestoryEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pDestoryEffect->Initialize();
	}
}