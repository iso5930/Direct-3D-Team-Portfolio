#include "StdAfx.h"
#include "WitchDoctor_LocustsSwarm_DummyEffect.h"

CWitchDoctor_LocustsSwarm_DummyEffect::CWitchDoctor_LocustsSwarm_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner , D3DXVECTOR3& _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_iMaxCnt = 9999;
	m_iMode = 0;
	m_fTime = 0.0f;
	m_fCreateTime = 1.f;
	m_fCreateTime2 = 1.f;
	m_vDir = _vDir;
	m_iCreateCnt = 0;
	m_iCreateCnt2 = 0;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f));
	AddComponent(pCollisionCom);
}

CWitchDoctor_LocustsSwarm_DummyEffect::~CWitchDoctor_LocustsSwarm_DummyEffect(void)
{
	Release();
}

void CWitchDoctor_LocustsSwarm_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CWitchDoctor_LocustsSwarm_DummyEffect::Update()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if (m_fTime > 5.f)
	{
		Destroy();
	}

	switch(m_iMode)
	{
	case  0:
		Mode0();
		break;

	case  1:
		break;

	}
	
	
	return 0;
}

void CWitchDoctor_LocustsSwarm_DummyEffect::Render()
{
	CEffect::Render();
}

void CWitchDoctor_LocustsSwarm_DummyEffect::Release()
{
}

void CWitchDoctor_LocustsSwarm_DummyEffect::Mode0()
{
	m_fCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fCreateTime2 += CTimeMgr::GetInstance()->GetDeltaTime();

	if (m_fCreateTime > 0.2f)
	{
		m_fCreateTime = 0.0f;
		CWitchDoctor_LocustsSwarmEffect* pLocustsSwarmEffect = NULL;
		CBufferCom* pBufferCom = NULL;
		CTransformCom* pTransformCom = NULL;
		
		D3DXVECTOR3 vRight ;

		D3DXVec3Cross(&vRight , &D3DXVECTOR3(0.f , 1.f ,0.f) ,&m_vDir);
		D3DXVec3Normalize(&vRight ,&vRight);
		vRight = vRight * (rand() % 20 - 10.f ) ; 

		if (m_iCreateCnt == 0 )
		{
			pLocustsSwarmEffect = new CWitchDoctor_LocustsSwarmEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pOwner->GetLayer()->AddObject(pLocustsSwarmEffect, LAYER_TYPE_EFFECT);
			pTransformCom = (CTransformCom*)pLocustsSwarmEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos - ( m_vDir * 50) + vRight ;
			pTransformCom->m_vPos.y += 100.f;
			pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;  
			pLocustsSwarmEffect->Initialize();
		}
		else if (m_iCreateCnt == 1 )
		{
			pLocustsSwarmEffect = new CWitchDoctor_LocustsSwarmEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pOwner->GetLayer()->AddObject(pLocustsSwarmEffect, LAYER_TYPE_EFFECT);
			pTransformCom = (CTransformCom*)pLocustsSwarmEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos ;
			pTransformCom->m_vPos.y += 100.f;
			pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;  	
			pLocustsSwarmEffect->Initialize();
		}
		else if (m_iCreateCnt == 2 )
		{
			pLocustsSwarmEffect = new CWitchDoctor_LocustsSwarmEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pOwner->GetLayer()->AddObject(pLocustsSwarmEffect, LAYER_TYPE_EFFECT);
			pTransformCom = (CTransformCom*)pLocustsSwarmEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + ( m_vDir * 50) + vRight;
			pTransformCom->m_vPos.y += 100.f;
			pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;	
			pLocustsSwarmEffect->Initialize();
			m_iMode = 1;
		}
		
		++m_iCreateCnt;

	}

	if (m_fCreateTime2 > 0.04f)
	{
		m_fCreateTime2 = 0.0f; 
		
		CWitchDoctor_LocustsSwarm_CloudEffect* pLocustsSwarm_CloudEffect = NULL;
		CBufferCom* pBufferCom = NULL;
		CTransformCom* pTransformCom = NULL;

		pLocustsSwarm_CloudEffect = new CWitchDoctor_LocustsSwarm_CloudEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner , m_vDir);
		m_pOwner->GetLayer()->AddObject(pLocustsSwarm_CloudEffect, LAYER_TYPE_EFFECT);
		pTransformCom = (CTransformCom*)pLocustsSwarm_CloudEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + ( m_vDir * ((m_iCreateCnt2 * 15 ) - 50.f) );
		pTransformCom->m_vPos.y += 100.f + (rand() % 20 - 10.f);
		pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;  
		pLocustsSwarm_CloudEffect->Initialize();
		++m_iCreateCnt2;

	}
	

}
