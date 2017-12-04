#include "StdAfx.h"
#include "Wizard_EnergyTwister_TornadoEffect.h"

CWizard_EnergyTwister_TornadoEffect::CWizard_EnergyTwister_TornadoEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = *_pDir;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Twister"));
	((CDynamicMesh*)(pBufferCom->m_BufferVec[0]))->m_pAnimController->SetAnimation(0);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 16;
	AddComponent(pRenderCom);

	m_fTime = 0.f;

	m_pTwisterEffect = NULL;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f));
	AddComponent(m_pCollisionCom);

	m_iMaxCnt = 99999;

	m_pCell = NULL;
	m_fDamegaTime = 0.f;

	// Coef
	m_fCoef = 0.76326f;
}

CWizard_EnergyTwister_TornadoEffect::~CWizard_EnergyTwister_TornadoEffect(void)
{
	Release();
}

void CWizard_EnergyTwister_TornadoEffect::Initialize()
{
	CEffect::Initialize();

	m_pTwisterEffect = new CWizard_EnergyTwister_TwisterEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTwisterEffect);
	m_pTwisterEffect->Initialize();

	CNaviCell* pCell = CPathFindMgr::GetInstance()->FindCell(&m_pTransformCom->m_vPos);

	if(pCell != NULL)
	{
		m_pCell = pCell;
	}
}

int CWizard_EnergyTwister_TornadoEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fDamegaTime += CTimeMgr::GetInstance()->GetDeltaTime();

	D3DXVECTOR3 vNextPos = m_pTransformCom->m_vPos + m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
	
	CNaviCell* pNextCell = NULL;

	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pCell, &vNextPos, &pNextCell);

	m_pTransformCom->m_vPos = vNextPos;
	m_pCell = pNextCell;
	
	m_pTransformCom->m_vAngle.y += D3DXToRadian(720.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 10.f)
	{
		Destroy();
	}

	if(m_fDamegaTime >= 0.3f)
	{
		m_fDamegaTime = 0.f;
		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}

	// Map Check
	vector<CObject*> vecMap;
	m_pOwner->GetLayer()->FindObjects(vecMap, _T("Map"), LAYER_TYPE_MAP);

	// Variable
	CTransformCom* pMapTransformCom;
	CBufferCom* pMapBufferCom;
	CStaticMesh* pMapStaticMesh;
	IntersectInfo intersectInfo;

	for(size_t i = 0; i < vecMap.size(); ++i)
	{
		D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 80.f, 0.f);
		D3DXVECTOR3 vDir(0.f, -1.f, 0.f);

		// MapTransformCom
		pMapTransformCom = (CTransformCom*)vecMap[i]->GetComponent(COM_TYPE_TRANSFORM);

		// MapBufferCom
		pMapBufferCom = (CBufferCom*)vecMap[i]->GetComponent(COM_TYPE_BUFFER);

		// MapStaticMesh
		pMapStaticMesh = (CStaticMesh*)pMapBufferCom->m_BufferVec[0];

		// Intersect
		D3DXIntersect(pMapStaticMesh->m_pMesh, &(vPos - pMapTransformCom->m_vPos), &vDir, &intersectInfo.bHit, &intersectInfo.dwFaceIndex, &intersectInfo.u, &intersectInfo.v, &intersectInfo.dist, &intersectInfo.pBuffer, &intersectInfo.dwCountOfHits);

		if(intersectInfo.bHit)
		{
			m_pTransformCom->m_vPos = m_pTransformCom->m_vPos + vDir * (intersectInfo.dist - 80.f);
		}
	}

	return 0;
}

void CWizard_EnergyTwister_TornadoEffect::Render()
{
	CEffect::Render();
}

void CWizard_EnergyTwister_TornadoEffect::Release()
{
	if(m_pTwisterEffect != NULL)
	{
		m_pTwisterEffect->Destroy();
		m_pTwisterEffect = NULL;
	}
}