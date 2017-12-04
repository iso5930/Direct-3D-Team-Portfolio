#include "StdAfx.h"
#include "SkeletonKing_SummonCompelete.h"

CSkeletonKing_SummonCompelete::CSkeletonKing_SummonCompelete(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos, bool _bCreate)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos= *_pPos;
	m_vOriginPos = *_pPos;
	
	// Create
	m_bCreate = _bCreate;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("SkeletonKing_EctoplasmBase"));
	AddComponent(pMaterialCom);
	
	m_fSize = 0.0f;

}

CSkeletonKing_SummonCompelete::~CSkeletonKing_SummonCompelete(void)
{
	Release();
}

void CSkeletonKing_SummonCompelete::Initialize()
{
	CEffect::Initialize();
}

int CSkeletonKing_SummonCompelete::Update()
{
	CEffect::Update();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() * 2;

	m_fSize += CTimeMgr::GetInstance()->GetDeltaTime() * 5;

	m_pTransformCom->m_vSize += D3DXVECTOR3(m_fSize, m_fSize, m_fSize);

	m_pTransformCom->m_vPos.y += CTimeMgr::GetInstance()->GetDeltaTime() * 40;

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);

	/*
	D3DXMATRIX matBill = *CCameraMgr::GetInstance()->GetBillBoard();

	D3DXMATRIX matTrans, matScale;
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);

	m_pTransformCom->m_mWorld = matScale * matBill * matTrans;
	*/

	if(m_fAlpha > 1.f)
	{
		if(m_bCreate)
		{
			int iRand = rand() % 2;
			CTransformCom* pTransformCom;
			
			if(iRand == 0)
			{
				//CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&m_pTransformCom->m_vPos);
				//CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, pNaviCell, &m_pTransformCom->m_vPos, &pNaviCell);

				CSkeleton_OneHand_Blue* pMonster = new CSkeleton_OneHand_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_OneHand_Blue_Spawn);
			}

			if(iRand == 1)
			{
				//CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&m_pTransformCom->m_vPos);
				//CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, pNaviCell, &m_pTransformCom->m_vPos, &pNaviCell);

				CSkeleton_Shield_Mint* pMonster = new CSkeleton_Shield_Mint(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
				m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
				pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = m_pTransformCom->m_vPos;
				pMonster->Initialize();
				pMonster->SetState(new CSkeleton_Shield_Mint_Spawn);
			}
			
		}
		Destroy();
	}

	return 0;
}

void CSkeletonKing_SummonCompelete::Render()
{
	CEffect::Render();
}

void CSkeletonKing_SummonCompelete::Release()
{

}

