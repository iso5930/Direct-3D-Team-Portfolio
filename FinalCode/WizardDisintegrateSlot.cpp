#include "StdAfx.h"
#include "WizardDisintegrateSlot.h"

CWizardDisintegrateSlot::CWizardDisintegrateSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_DISINTEGRATE;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

	// m_fTickTime
	m_fTickTime = 0.0f;

	m_iSoundNum = 0;

	m_pRayEffect = NULL;
	m_pFlashEffect[0] = NULL;
	m_pFlashEffect[1] = NULL;
	m_pHitEffect[0] = NULL;
	m_pHitEffect[1] = NULL;
}

CWizardDisintegrateSlot::~CWizardDisintegrateSlot()
{
}

SLOT_RESULT CWizardDisintegrateSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	D3DXVECTOR3 vPos;
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPos = pTransformCom->m_vPos;
	}

	// Check Vision
	if (m_pOwner->GetStat()->iVision < 18 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("비전력이 부족합니다."));
		return SLOT_RESULT_VISION_EMPTY;
	}
	
	// Begin
	CSlot::Begin(_iMode);

	m_iSoundNum = CSoundMgr::GetInstance()->PlaySoundForPlayerBGM(_T("DISINTEGRATE_Loop.ogg"));
		
	// Vision
	m_pOwner->GetStat()->iVision -= int(18 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

	CTransformCom* pTransformCom = NULL;
	D3DXVECTOR3 vRayPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f) + (vDir * 50.f);

	// Ray
	m_pRayEffect = new CWizard_Disintegrate_RayEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pRayEffect, LAYER_TYPE_EFFECT);
	m_pRayEffect->Initialize();

	// Flash_1
	m_pFlashEffect[0] = new CWizard_Disintegrate_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pFlashEffect[0], LAYER_TYPE_EFFECT);
	
	// Flash_1_Pos
	pTransformCom = (CTransformCom*)m_pFlashEffect[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vRayPos;
	pTransformCom->m_vAngle.z = D3DXToRadian(float(rand() % 360));
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	m_pFlashEffect[0]->Initialize();
	
	// Flash_2
	m_pFlashEffect[1] = new CWizard_Disintegrate_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pFlashEffect[1], LAYER_TYPE_EFFECT);
	
	// Flash_2_Pos
	pTransformCom = (CTransformCom*)m_pFlashEffect[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vRayPos;
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pTransformCom->m_vAngle.z = D3DXToRadian(float(rand() % 360));
	m_pFlashEffect[1]->Initialize();

	// Hit_Effect1
	m_pHitEffect[0] = new CWizard_Disintegrate_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pHitEffect[0], LAYER_TYPE_EFFECT);

	// Hit_Effect_Pos1
	pTransformCom = (CTransformCom*)m_pHitEffect[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vAngle.z = D3DXToRadian(float(rand() % 360));
	pTransformCom->m_vAngle.y = D3DXToRadian(135.f);
	m_pHitEffect[0]->Initialize();

	// Hit_Effect2
	m_pHitEffect[1] = new CWizard_Disintegrate_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pHitEffect[1], LAYER_TYPE_EFFECT);

	// Hit_Effect_Pos2
	pTransformCom = (CTransformCom*)m_pHitEffect[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vAngle.z = D3DXToRadian(float(rand() % 360));
	pTransformCom->m_vAngle.y = D3DXToRadian(135.f);
	m_pHitEffect[1]->Initialize();

	m_pHitEffect[0]->AddCollisionComponent();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardDisintegrateSlot::Action()
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	D3DXVECTOR3 vPos;
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPos = pTransformCom->m_vPos;
	}

	// TickTime
	m_fTickTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTickTime > 0.25f)
	{
		m_fTickTime = 0.0f;

		// Check Vision
		if (m_pOwner->GetStat()->iVision < 9 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("비전력이 부족합니다."));
			return SLOT_RESULT_VISION_EMPTY;
		}

		// Vision
		m_pOwner->GetStat()->iVision -= int(9 * (1.0f - m_pOwner->GetReducedVisionConsumption()));	
	}

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

	CTransformCom* pTransformCom = NULL;

	D3DXVECTOR3 vSourPos;
	float fAngleX = D3DXToRadian(90.f);

	// Monster Check
	vector<CObject*> vecFindMonster;
	m_pOwner->GetLayer()->FindObjects(vecFindMonster, _T("Monster"), LAYER_TYPE_MONSTER);

	float fMonsterDist = 700.f;
	D3DXVECTOR3 vMonsterPos(0.f, 0.f, 0.f);

	for(size_t i = 0; i < vecFindMonster.size(); ++i)
	{
		vSourPos = m_pTransformCom->m_vPos + (vDir * 50.f);
		D3DXVECTOR3 vDestPos = vSourPos + (vDir * 750.f);

		((CMonster*)vecFindMonster[i])->Intersect(&vSourPos, &vDestPos);
		D3DXVECTOR3 vDist = vDestPos - vSourPos;
		float fLength = D3DXVec3Length(&vDist);

		if(fMonsterDist >= fLength)
		{
			fMonsterDist = fLength;
			vMonsterPos = vDestPos;
		}
	}

	// DynamicProb Check
	vector<CObject*> vecDynamicProb;	
	m_pOwner->GetLayer()->FindObjects(vecDynamicProb, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

	float fDynamicDist = 700.f;
	D3DXVECTOR3 vDynamicPos(0.f, 0.f, 0.f);

	for(size_t i = 0; i < vecDynamicProb.size(); ++i)
	{
		vSourPos = m_pTransformCom->m_vPos + (vDir * 50.f);
		D3DXVECTOR3 vDestPos = vSourPos + (vDir * 750.f);

		((CDynamicProb*)vecDynamicProb[i])->Intersect(&vSourPos, &vDestPos);
		D3DXVECTOR3 vDist = vDestPos - vSourPos;
		float fLength = D3DXVec3Length(&vDist);

		if(fDynamicDist >= fLength)
		{
			fDynamicDist = fLength;
			vDynamicPos = vDestPos;
		}
	}

	// StaticProb Check
	vector<CObject*> vecStaticProb;
	m_pOwner->GetLayer()->FindObjects(vecStaticProb, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);

	float fStaticDist = 700.f;
	D3DXVECTOR3 vStaticPos(0.f, 0.f, 0.f);

	for(size_t i = 0; i < vecStaticProb.size(); ++i)
	{
		vSourPos = m_pTransformCom->m_vPos + (vDir * 50.f);
		D3DXVECTOR3 vDestPos = vSourPos + (vDir * 750.f);

		((CStaticProb*)vecStaticProb[i])->Intersect(&vSourPos, &vDestPos);
		D3DXVECTOR3 vDist = vDestPos - vSourPos;
		float fLength = D3DXVec3Length(&vDist);

		if(fStaticDist >= fLength)
		{
			fStaticDist = fLength;
			vStaticPos = vDestPos;
		}
	}

	// Map Check
	vector<CObject*> vecMap;
	m_pOwner->GetLayer()->FindObjects(vecMap, _T("Map"), LAYER_TYPE_MAP);

	float fMapDist = 700.f;
	D3DXVECTOR3 vMapPos(0.f, 0.f, 0.f);
	
	// Variable
	CTransformCom* pMapTransformCom;
	CBufferCom* pMapBufferCom;
	CStaticMesh* pMapStaticMesh;
	IntersectInfo intersectInfo;
	
	for(size_t i = 0; i < vecMap.size(); ++i)
	{
		vSourPos = m_pTransformCom->m_vPos + (vDir * 50.f) + D3DXVECTOR3(0.0f, 70.f, 0.0f);

		// MapTransformCom
		pMapTransformCom = (CTransformCom*)vecMap[i]->GetComponent(COM_TYPE_TRANSFORM);

		// MapBufferCom
		pMapBufferCom = (CBufferCom*)vecMap[i]->GetComponent(COM_TYPE_BUFFER);

		// MapStaticMesh
		pMapStaticMesh = (CStaticMesh*)pMapBufferCom->m_BufferVec[0];

		// Intersect
		D3DXIntersect(pMapStaticMesh->m_pMesh, &(vSourPos - pMapTransformCom->m_vPos), &vDir, &intersectInfo.bHit, &intersectInfo.dwFaceIndex, &intersectInfo.u, &intersectInfo.v, &intersectInfo.dist, &intersectInfo.pBuffer, &intersectInfo.dwCountOfHits);
		
		if(intersectInfo.bHit)
		{
			if(fMapDist >= intersectInfo.dist)
			{
				fMapDist = intersectInfo.dist;
				vMapPos = vSourPos + vDir * fStaticDist;
			}
		}
	}

	float fRayDist = 0.f;
	D3DXVECTOR3 vRayPos(0.f, 0.f, 0.f);

	//가장 작은 값을 찾아
	if(fStaticDist >= fMonsterDist && fDynamicDist >= fMonsterDist && fMapDist >= fMonsterDist)
	{
		fRayDist = fMonsterDist;
		vRayPos = vMonsterPos;
	}
	else if(fMonsterDist >= fStaticDist && fDynamicDist >= fStaticDist && fMapDist >= fStaticDist)
	{
		fRayDist = fStaticDist;
		vRayPos = vStaticPos;
	}
	else if(fMonsterDist >= fDynamicDist && fStaticDist >= fDynamicDist && fMapDist >= fDynamicDist)
	{
		fRayDist = fDynamicDist;
		vRayPos = vDynamicPos;
	}
	else if(fMonsterDist >= fMapDist && fStaticDist >= fMapDist && fDynamicDist >= fMapDist)
	{
		fRayDist = fMapDist;
		vRayPos = vMapPos;
	}
	else
	{
		fRayDist = 700.f;
	}

	// Result
	if(fRayDist >= 700.f)
	{
		vRayPos = vPos;
	}
	else
	{
		D3DXVECTOR3 vRay = vRayPos - m_pTransformCom->m_vPos;
		D3DXVec3Normalize(&vRay, &vRay);

		float fDot = D3DXVec3Dot(&vRay, &vDir);
		fAngleX -= acosf(fDot);
	}

	// StartPos
	vSourPos = m_pTransformCom->m_vPos + (vDir * 50.f) + D3DXVECTOR3(0.0f, 70.f, 0.0f);

	// RayPos
	pTransformCom = (CTransformCom*)m_pRayEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vSourPos + (vDir * fRayDist / 2.f);
	pTransformCom->m_vAngle.x = fAngleX;
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pTransformCom->m_vSize.y = fRayDist;

	// FlashPos_1
	pTransformCom = (CTransformCom*)m_pFlashEffect[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vSourPos;
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	
	// FlashPos_2
	pTransformCom = (CTransformCom*)m_pFlashEffect[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vSourPos;
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;

	// HitFlash_1
	pTransformCom = (CTransformCom*)m_pHitEffect[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vSourPos + vDir * fRayDist;
	
	// HitFlash_2
	pTransformCom = (CTransformCom*)m_pHitEffect[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vSourPos + vDir * fRayDist;

	m_pHitEffect[0]->ResetCollision();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardDisintegrateSlot::End()
{
	if(m_pRayEffect != NULL)
	{
		m_pRayEffect->Destroy();
		m_pRayEffect = NULL;
	}

	for(int i = 0; i < 2; ++i)
	{
		if(m_pFlashEffect[i] != NULL)
		{
			m_pFlashEffect[i]->Destroy();
			m_pFlashEffect[i] = NULL;
		}

		if(m_pHitEffect[i] != NULL)
		{
			m_pHitEffect[i]->Destroy();
			m_pHitEffect[i] = NULL;
		}
	}	

	CSoundMgr::GetInstance()->StopSoundForPlayerBGM(m_iSoundNum);

	return SLOT_RESULT_NULL;
}