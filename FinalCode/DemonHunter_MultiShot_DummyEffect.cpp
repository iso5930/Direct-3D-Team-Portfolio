#include "StdAfx.h"
#include "DemonHunter_MultiShot_DummyEffect.h"

CDemonHunter_MultiShot_DummyEffect::CDemonHunter_MultiShot_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;
	m_vDir = (*_pDir);
}

CDemonHunter_MultiShot_DummyEffect::~CDemonHunter_MultiShot_DummyEffect(void)
{
	Release();
}

void CDemonHunter_MultiShot_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_MultiShot_DummyEffect::Update()
{
	CEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += fTime;
	m_fAccTime += fTime;

	if(m_fAccTime >= 0.4f)
		Destroy();

	if(m_fTime >= 0.1f)
	{
		m_fTime = (rand() % 10) / 100.f;

		int iRand = (rand() % 5) + 4;

		// YÃà È¸Àü
		for(int i = 0; i < iRand; ++i)
		{
			int iAngle = (rand() % 60) - 30;

			D3DXMATRIX matRotY;
			D3DXVECTOR3 vDir;

			D3DXMatrixRotationY(&matRotY, D3DXToRadian(iAngle));			
			D3DXVec3TransformNormal(&vDir, &m_vDir, &matRotY);

			CDemonHunter_MultiShot_ArrowEffect* pArrowEffect = new CDemonHunter_MultiShot_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
			m_pLayer->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

			//Trasnform
			CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f) + m_vDir * 30.f;
			pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y + D3DXToRadian(iAngle);
			pArrowEffect->Initialize();
		}
	}

	return 0;
}

void CDemonHunter_MultiShot_DummyEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_MultiShot_DummyEffect::Release()
{

}