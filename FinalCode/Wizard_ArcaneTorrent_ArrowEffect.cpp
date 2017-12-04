#include "StdAfx.h"
#include "Wizard_ArcaneTorrent_ArrowEffect.h"

CWizard_ArcaneTorrent_ArrowEffect::CWizard_ArcaneTorrent_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vEndPos = *_vDestPos;
	m_fDetail = 0.f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_pTrailEffect = NULL;
	m_pArrowTrailEffect = NULL;
}

CWizard_ArcaneTorrent_ArrowEffect::~CWizard_ArcaneTorrent_ArrowEffect(void)
{
	Release();
}

void CWizard_ArcaneTorrent_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	int iRandX = rand() % 50;
	int iRandZ = rand() % 50;

	m_vEndPos += D3DXVECTOR3((float)iRandX, 0.f, (float)iRandZ);

	m_pTrailEffect = new CWizard_ArcaneTorrent_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	m_pArrowTrailEffect = new CWizard_ArcaneTorrent_ArrowTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pArrowTrailEffect, LAYER_TYPE_EFFECT);
	m_pArrowTrailEffect->Initialize();
	
	m_vStartPos = m_pTransformCom->m_vPos;

	D3DXVECTOR3 vCenter = (m_vEndPos - m_vStartPos) / 2.f;
	vCenter = m_vStartPos + vCenter;

	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, &vCenter);

	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);

	int iRand = (rand() % 180) - 90;
	D3DXMATRIX matRotAxis;

	D3DXMatrixRotationAxis(&matRotAxis, &vDir, D3DXToRadian(iRand));

	D3DXVec3TransformNormal(&vUp, &vUp, &matRotAxis);
	
	iRand = rand() % 50;

	vUp = vUp * float(iRand + 300);

	m_vBezierPos = vCenter + vUp;
}

int CWizard_ArcaneTorrent_ArrowEffect::Update()
{
	CEffect::Update();

	m_fDetail += (1.f / 40.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();
	GetBezier(&m_pTransformCom->m_vPos, &m_vStartPos, &m_vBezierPos, &m_vEndPos, m_fDetail);

	if(m_fDetail >= 1.f)
	{
		Destroy();

		CWizard_ArcaneTorrent_DestoryEffect* pDestoryEffect = new CWizard_ArcaneTorrent_DestoryEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDestoryEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDestoryEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pDestoryEffect->Initialize();
	}

	return 0;
}

void CWizard_ArcaneTorrent_ArrowEffect::Render()
{
	CEffect::Render();
}

void CWizard_ArcaneTorrent_ArrowEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}

	if(m_pArrowTrailEffect != NULL)
	{
		m_pArrowTrailEffect->Destroy();
		m_pArrowTrailEffect = NULL;
	}
}