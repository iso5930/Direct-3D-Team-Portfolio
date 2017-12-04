#include "StdAfx.h"
#include "Monk_ExplodingPalm_DummyEffect.h"

CMonk_ExplodingPalm_DummyEffect::CMonk_ExplodingPalm_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{		
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
}

CMonk_ExplodingPalm_DummyEffect::~CMonk_ExplodingPalm_DummyEffect(void)
{
	Release();
}

void CMonk_ExplodingPalm_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_ExplodingPalm_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.6f)
	{
		Destroy();

		Bone tBone;
		ZeroMemory(&tBone, sizeof(Bone));
		CDynamicMesh* pDynamicMesh = NULL;

		CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
		pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
		tBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
		tBone.mWorld = tBone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

		D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXVec3TransformCoord(&vPos, &vPos, &tBone.mWorld);

		CMonk_ExplodingPalm_AttackEffect* pAttackEffect = new CMonk_ExplodingPalm_AttackEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pAttackEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAttackEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos - D3DXVECTOR3(0.f, 30.f, 0.f);
		pTransformCom->m_vAngle = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vAngle;
		pAttackEffect->Initialize();

		CMonk_ExplodingPalm_RefractionEffect* pRefractionEffect = new CMonk_ExplodingPalm_RefractionEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pRefractionEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pRefractionEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos;
		pRefractionEffect->Initialize();
	}

	return 0;
}

void CMonk_ExplodingPalm_DummyEffect::Render()
{
	CEffect::Render();
}

void CMonk_ExplodingPalm_DummyEffect::Release()
{

}
