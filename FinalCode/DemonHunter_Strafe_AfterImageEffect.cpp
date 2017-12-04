#include "StdAfx.h"
#include "DemonHunter_Strafe_AfterImageEffect.h"

CDemonHunter_Strafe_AfterImageEffect::CDemonHunter_Strafe_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	m_pBufferCom = new CBufferCom;
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Boots"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hair"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hands"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Pants"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Upper"));
	AddComponent(m_pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 11;
	AddComponent(pRenderCom);

	for(int i = 0; i < 2; ++i)
	{
		m_pWeaponEffect[i] = NULL;
	}

	m_fTime = 0.f;
}

CDemonHunter_Strafe_AfterImageEffect::~CDemonHunter_Strafe_AfterImageEffect(void)
{
	Release();
}

void CDemonHunter_Strafe_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	for(size_t i = 0; i < m_pBufferCom->m_BufferVec.size(); ++i)
	{
		((CDynamicMesh*)(m_pBufferCom->m_BufferVec[i]))->m_pAnimController->SetAnimation(33);
	}

	m_pWeaponEffect[0] = new CDemonHunter_Strafe_WeaponEffect(NULL, OBJ_TYPE_DYNAMIC, this, _T("Item_HandXBow_Base0"), "left_weapon");
	m_pLayer->AddObject(m_pWeaponEffect[0], LAYER_TYPE_EFFECT);
	
	CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponEffect[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vAngle.z = D3DXToRadian(180.f);
	m_pWeaponEffect[0]->Initialize();

	m_pWeaponEffect[1] = new CDemonHunter_Strafe_WeaponEffect(NULL, OBJ_TYPE_DYNAMIC, this, _T("Item_HandXBow_Base0"), "right_weapon");
	m_pLayer->AddObject(m_pWeaponEffect[1], LAYER_TYPE_EFFECT);
	m_pWeaponEffect[1]->Initialize();
}	

int CDemonHunter_Strafe_AfterImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	CBufferCom* pBufferCom = ((CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER));
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	
	m_pTransformCom->m_mWorld *= ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mTrans;

	if(m_fTime >= 0.2f)
	{
		m_fTime = 0.f;

		int iRand = rand() % 360;
		
		float fMin = 800.f;
		int iFindMonster = -1;
		vector<CObject*> vecFindMonster;
		CTransformCom* pFindMonster;
		
		CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

		m_pLayer->FindObjects(vecFindMonster, _T("Monster"), LAYER_TYPE_MONSTER);


		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("ArrowAttack.ogg"));


		if(vecFindMonster.size() != 0)
		{
			for(size_t i = 0; i < vecFindMonster.size(); ++i)
			{
				CTransformCom* pTransformCom = (CTransformCom*)vecFindMonster[i]->GetComponent(COM_TYPE_TRANSFORM);

				D3DXVECTOR3 vLength = pTransformCom->m_vPos - pOwnerTransformCom->m_vPos;
				float fDist = D3DXVec3Length(&vLength);

				if(fDist <= fMin)
				{
					fMin = fDist;
					iFindMonster = i;
					pFindMonster = pTransformCom;
				}
			}
		}

		if(iFindMonster != -1)
		{
			float fAngle = pOwnerTransformCom->m_vAngle.y;

			D3DXVECTOR3 vDir = pFindMonster->m_vPos - pOwnerTransformCom->m_vPos;
			vDir.y = 0.f;
			D3DXVec3Normalize(&vDir, &vDir);

			// DotX
			float fDotX = D3DXVec3Dot(&-pOwnerTransformCom->m_vAxisX, &vDir);
			fDotX = RevisionDot(fDotX);

			// DotZ
			float fDotZ = D3DXVec3Dot(&-pOwnerTransformCom->m_vAxisZ, &vDir);
			fDotZ = RevisionDot(fDotZ);
			
			if(fDotX > 0.0f)
				fAngle = fAngle + acosf(fDotZ);
			else
				fAngle = fAngle - acosf(fDotZ);
						
			CDemonHunter_Strafe_FlashEffect* pFlashEffect = new CDemonHunter_Strafe_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pLayer->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (pOwnerTransformCom->m_vPos + vDir * 90.f) + D3DXVECTOR3(0.f, 60.f, 0.f);
			pTransformCom->m_vAngle.y = fAngle + D3DXToRadian(180.f);
			pFlashEffect->Initialize();
			
			CDemonHunter_Strafe_ArrowEffect* pArrowEffect = new CDemonHunter_Strafe_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
			m_pLayer->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

			pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (pOwnerTransformCom->m_vPos + vDir * 90.f) + D3DXVECTOR3(0.f, 60.f, 0.f);
			pTransformCom->m_vAngle.y = fAngle + D3DXToRadian(180.f);
			pArrowEffect->Initialize();
		}
		else 
		{
			D3DXMATRIX matRotY;
			D3DXMatrixRotationY(&matRotY, D3DXToRadian(iRand));
			D3DXVECTOR3 vDir(0.f, 0.f, 1.f);
			D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

			CDemonHunter_Strafe_FlashEffect* pFlashEffect = new CDemonHunter_Strafe_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pLayer->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos + vDir * 90.f) + D3DXVECTOR3(0.f, 60.f, 0.f);
			pTransformCom->m_vAngle.y = D3DXToRadian(iRand);
			pFlashEffect->Initialize();

			CDemonHunter_Strafe_ArrowEffect* pArrowEffect = new CDemonHunter_Strafe_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
			m_pLayer->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

			pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos + vDir * 90.f) + D3DXVECTOR3(0.f, 60.f, 0.f);
			pTransformCom->m_vAngle.y = D3DXToRadian(iRand);
			pArrowEffect->Initialize();
		}		
	}

	return 0;
}

void CDemonHunter_Strafe_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Strafe_AfterImageEffect::Release()
{
	for(int i = 0; i < 2; ++i)
	{
		if(m_pWeaponEffect[i] != NULL)
		{
			m_pWeaponEffect[i]->Destroy();
			m_pWeaponEffect[i] = NULL;
		}
	}	
}