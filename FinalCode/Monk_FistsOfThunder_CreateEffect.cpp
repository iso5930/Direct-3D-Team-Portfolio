#include "StdAfx.h"
#include "Monk_FistsOfThunder_CreateEffect.h"

CMonk_FistsOfThunder_CreateEffect::CMonk_FistsOfThunder_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fCreateTime, int _iMode)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fCreateTime = _fCreateTime;
	m_fTime = 0.f;
	m_iMode = _iMode;
}

CMonk_FistsOfThunder_CreateEffect::~CMonk_FistsOfThunder_CreateEffect(void)
{
	Release();
}

void CMonk_FistsOfThunder_CreateEffect::Initialize()
{
	CEffect::Initialize();
}	

int CMonk_FistsOfThunder_CreateEffect::Update()
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

	case 2:
		Mode1();
		break;

	}

	

	return 0;
}

void CMonk_FistsOfThunder_CreateEffect::Render()
{
	CEffect::Render();
}

void CMonk_FistsOfThunder_CreateEffect::Release()
{

}

void CMonk_FistsOfThunder_CreateEffect::Mode1()
{
	if(m_fTime >= m_fCreateTime)
	{
		if (m_iMode == 2 )
		{
			CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FISTS_OF_THUNDER3.ogg"));
		}
		else
			CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FISTS_OF_THUNDER1.ogg"));

		Bone tBone;
		ZeroMemory(&tBone, sizeof(Bone));
		CDynamicMesh* pDynamicMesh = NULL;

		CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
		pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
		tBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
		tBone.mWorld = tBone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

		D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXVec3TransformCoord(&vPos, &vPos, &tBone.mWorld);

		CMonk_FistsOfThunder_FlashEffect* pFlashEffect = new CMonk_FistsOfThunder_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos;
		pFlashEffect->Initialize();

		Destroy();
	}
}

void CMonk_FistsOfThunder_CreateEffect::Mode2()
{
	if(m_fTime >= m_fCreateTime)
	{
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FISTS_OF_THUNDER2.ogg"));

		Bone tBone;
		ZeroMemory(&tBone, sizeof(Bone));
		CDynamicMesh* pDynamicMesh = NULL;

		CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
		pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
		tBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
		tBone.mWorld = tBone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

		D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXVec3TransformCoord(&vPos, &vPos, &tBone.mWorld);

		CMonk_FistsOfThunder_FlashEffect* pFlashEffect = new CMonk_FistsOfThunder_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos;
		pFlashEffect->Initialize();

		Destroy();
	}
}