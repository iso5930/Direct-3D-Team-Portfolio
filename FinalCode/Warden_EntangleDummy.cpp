#include "StdAfx.h"
#include "Warden_EntangleDummy.h"

CWarden_EntangleDummy::CWarden_EntangleDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);
	
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	// SkillType
	m_eSkillType = SKILL_TYPE_ENTANGLE;
	m_iMaxCnt = 1000;

	m_bDestroyCheck = false;

	m_bEffect = false;

	m_fDestroyTime = 0.0f;
}

CWarden_EntangleDummy::~CWarden_EntangleDummy(void)
{
	Release();
}

void CWarden_EntangleDummy::Initialize()
{
	CEffect::Initialize();

	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
	m_pTransformCom->m_vPos = pPlayerTransformCom->m_vPos;
}

int CWarden_EntangleDummy::Update()
{
	CEffect::Update();

	if(!m_bEffect)
	{
		for(int i = 0; i < 25; ++i)
		{
			CObject* pPlayer = NULL;
			m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
			if(pPlayer == NULL)
				return NULL;

			// PlayerTransformCom
			CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

			int iRand = rand() % 400 + 200;
			D3DXVECTOR3 vDir(0.f, 0.f, 1.f);
			D3DXMATRIX matRotY;
			D3DXMatrixRotationY(&matRotY, D3DXToRadian((360 / 25) * i));
			D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

			D3DXVECTOR3 vPos = pPlayerTransformCom->m_vPos + vDir * 50.f;

			CWarden_Entangle* pEntangleEffect = new CWarden_Entangle(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &D3DXVECTOR3(0.f, 0.f, 0.f));
			m_pOwner->GetLayer()->AddObject(pEntangleEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pEntangleEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = vPos;
			pTransformCom->m_vPos.y += iRand / 2.f;
			pTransformCom->m_vSize.x = 20.f;
			pTransformCom->m_vSize.y = (float)iRand;
			pTransformCom->m_vAngle.y = D3DXToRadian((360 / 25) * i);
			pEntangleEffect->Initialize();
			m_bDestroyCheck = true;
		}

		m_bEffect = true;
	}

	if(m_bDestroyCheck)
		m_fDestroyTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fDestroyTime > 2.f)
		Destroy();

	return 0;
}

void CWarden_EntangleDummy::Render()
{
	CEffect::Render();
}

void CWarden_EntangleDummy::Release()
{

}
