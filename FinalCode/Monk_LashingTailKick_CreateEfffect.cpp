#include "StdAfx.h"
#include "Monk_LashingTailKick_CreateEfffect.h"

CMonk_LashingTailKick_CreateEfffect::CMonk_LashingTailKick_CreateEfffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_vDir = _vDir;
}

CMonk_LashingTailKick_CreateEfffect::~CMonk_LashingTailKick_CreateEfffect(void)
{
	Release();
}

void CMonk_LashingTailKick_CreateEfffect::Initialize()
{
	CEffect::Initialize();
}	

int CMonk_LashingTailKick_CreateEfffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();

		CMonk_LashingTailKick_KickEffect* pKickEffect = new CMonk_LashingTailKick_KickEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, m_vDir);
		m_pLayer->AddObject(pKickEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTrnasformCom = (CTransformCom*)pKickEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTrnasformCom->m_vPos = m_pTransformCom->m_vPos;
		pTrnasformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pKickEffect->Initialize();
	}

	return 0;
}

void CMonk_LashingTailKick_CreateEfffect::Render()
{	
	CEffect::Render();
}

void CMonk_LashingTailKick_CreateEfffect::Release()
{

}
