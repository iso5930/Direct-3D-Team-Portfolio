#include "StdAfx.h"
#include "SkeletonSummoner_SummonSkeleton.h"

CSkeletonSummoner_SummonSkeleton::CSkeletonSummoner_SummonSkeleton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos= *_pPos;
	
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("SkeletonSummoner_SummonSkeleton"));
	AddComponent(pMaterialCom);
}

CSkeletonSummoner_SummonSkeleton::~CSkeletonSummoner_SummonSkeleton(void)
{
	Release();
}

void CSkeletonSummoner_SummonSkeleton::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_pTransformCom->m_vPos.y += 50.f;
}

int CSkeletonSummoner_SummonSkeleton::Update()
{
	CEffect::Update();


	m_pTransformCom->m_vAngle.z += D3DXToRadian(45.f) * 10 * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() / 2.f;

	if(m_fAlpha > 1.f)
	{
		CTransformCom* pTransformCom;

		TCHAR tszName[MIN_STR];
		ZeroMemory(tszName, sizeof(tszName));
		
		_tcscpy_s(tszName, MIN_STR, ((CMonster*)m_pOwner)->GetInfo()->tszName);

		if(lstrcmp(tszName, _T("고문당한 소환사")) == 0)
		{
			CSkeleton_Axe_Blue* pMonster = new CSkeleton_Axe_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
			m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
			pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos;
			pMonster->Initialize();
			pMonster->SetState(new CSkeleton_Axe_Blue_Spawn);
		}

		if(lstrcmp(tszName, _T("무덤 수호자")) == 0)
		{
			int iRand = rand() % 2;
			if(iRand == 0)
			{
				CSkeleton_OneHand_Mint* pMonster = new CSkeleton_OneHand_Mint(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_OneHand_Mint_Spawn);
			}

			if(iRand == 1)
			{
				CSkeleton_Shield_Brown* pMonster = new CSkeleton_Shield_Brown(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_Shield_Brown_Spawn);
			}
		}

		if(lstrcmp(tszName, _T("충직한 왕실 마법사")) == 0)
		{
			int iRand = rand() % 2;
				
			if(iRand == 0)
			{
				CSkeleton_Shield_Red* pMonster = new CSkeleton_Shield_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_Shield_Red_Spawn);
			}

			if(iRand == 1)
			{
				CSkeleton_Axe_Red* pMonster = new CSkeleton_Axe_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_Axe_Red_Spawn);
			}
		}
		Destroy();
	}

	return 0;
}

void CSkeletonSummoner_SummonSkeleton::Render()
{	
	CEffect::Render();
}

void CSkeletonSummoner_SummonSkeleton::Release()
{

}