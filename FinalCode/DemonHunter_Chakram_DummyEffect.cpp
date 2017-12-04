#include "StdAfx.h"
#include "DemonHunter_Chakram_DummyEffect.h"

CDemonHunter_Chakram_DummyEffect::CDemonHunter_Chakram_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = (*_pDir);

	m_pChakramEffect = NULL;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
}

CDemonHunter_Chakram_DummyEffect::~CDemonHunter_Chakram_DummyEffect(void)
{
	Release();
}

void CDemonHunter_Chakram_DummyEffect::Initialize()
{
	CEffect::Initialize();

	m_pChakramEffect = new CDemonHunter_Chakram_ChakramEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pChakramEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)m_pChakramEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
	m_pChakramEffect->Initialize();
}

int CDemonHunter_Chakram_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 4.f)
	{
		Destroy();
	}

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.y += D3DXToRadian(520.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CDemonHunter_Chakram_DummyEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Chakram_DummyEffect::Release()
{
	if(m_pChakramEffect != NULL)
	{
		m_pChakramEffect->Destroy();
		m_pChakramEffect = NULL;
	}
}