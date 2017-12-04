#include "Stdafx.h"
#include "PathFindCom.h"

CPathFindCom::CPathFindCom(PATH_TYPE _ePathType, float _fSpeed)
{
	// TransformCom
	m_pTransformCom = NULL;

	// Component Type
	m_eComType = COM_TYPE_PATH_FIND;

	// PathType
	m_ePathType = _ePathType;

	// Enable
	m_bEnable = false;

	// Speed
	m_fSpeed = _fSpeed;

	// Dir
	ZeroMemory(&m_vDir, sizeof(D3DXVECTOR3));

	// Dst
	ZeroMemory(&m_vDst, sizeof(D3DXVECTOR3));

	// Cell
	m_pCell = NULL;
}

CPathFindCom::~CPathFindCom()
{
	Release();
}

void CPathFindCom::Initialize()
{
	// Transform Component
	m_pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	// Find Cell
	CNaviCell* pCell = CPathFindMgr::GetInstance()->FindCell(&m_pTransformCom->m_vPos);
	if(pCell != NULL)
		m_pCell = pCell;

	// Add Group
	CPathFindMgr::GetInstance()->AddGroup(m_ePathType, m_pOwner);
}

int CPathFindCom::Update()
{
	// Initialize Dir
	ZeroMemory(&m_vDir, sizeof(D3DXVECTOR3));

	// Check Cell
	if(m_pCell == NULL)
	{
		m_pCell = CPathFindMgr::GetInstance()->FindCell(&m_pTransformCom->m_vPos);
		if(m_pCell == NULL)
			return 0;

		m_pCell->ForcePointToCellCollumn(&m_pTransformCom->m_vPos);
		m_pCell->Projection(&m_pTransformCom->m_vPos);
	}

	// Check IsIn
	if(m_pCell->IsIn(&m_pTransformCom->m_vPos) == false)
	{
		m_pCell->ForcePointToCellCollumn(&m_pTransformCom->m_vPos);
		m_pCell->Projection(&m_pTransformCom->m_vPos);
	}

	// Check Enable
	if(m_bEnable == false)
		return 0;

	switch(m_ePathType)
	{
	case PATH_TYPE_PLAYER:
		UpdatePlayer();
		break;

	case PATH_TYPE_MONSTER:
		UpdateMonster();
		break;

	case PATH_TYPE_FOLLOWER:
		UpdateFollower();
		break;
	}

	return 0;
}

void CPathFindCom::UpdatePlayer()
{
	// Check Dst
	if(Equals(m_vDst.x, m_pTransformCom->m_vPos.x, MAX_EPSILON) && Equals(m_vDst.z, m_pTransformCom->m_vPos.z, MAX_EPSILON))
	{
		m_bEnable = false;
		return;
	}

	// Dir
	m_vDir = m_vDst - m_pTransformCom->m_vPos;
	m_vDir.y = 0.0f;

	// Limit Speed
	if(D3DXVec3Length(&m_vDir) > m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime())
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_vDir = m_vDir * m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime();
	}

	// NextPos
	D3DXVECTOR3 vNextPos = m_pTransformCom->m_vPos + m_vDir;

	// Solution
	CNaviCell* pNextCell;
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pCell, &vNextPos, &pNextCell);

	// SetPos
	m_pTransformCom->m_vPos = vNextPos;

	// SetCell
	m_pCell = pNextCell;

	// Revision
	// Revision();
}

void CPathFindCom::UpdateMonster()
{
	// Check Dst
	if(Equals(m_vDst.x, m_pTransformCom->m_vPos.x, MAX_EPSILON) && Equals(m_vDst.z, m_pTransformCom->m_vPos.z, MAX_EPSILON))
	{
		m_bEnable = false;
		return;
	}

	// Dir
	m_vDir = m_vDst - m_pTransformCom->m_vPos;
	m_vDir.y = 0.0f;

	// Limit Speed
	if(D3DXVec3Length(&m_vDir) > m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime())
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_vDir = m_vDir * m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime();
	}

	// NextPos
	D3DXVECTOR3 vNextPos = m_pTransformCom->m_vPos + m_vDir;

	// Solution
	CNaviCell* pNextCell;
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pCell, &vNextPos, &pNextCell);

	// SetPos
	m_pTransformCom->m_vPos = vNextPos;

	// SetCell
	m_pCell = pNextCell;

	// Revision
	Revision();
}

void CPathFindCom::UpdateFollower()
{
	// Check Dst
	if(Equals(m_vDst.x, m_pTransformCom->m_vPos.x, MAX_EPSILON) && Equals(m_vDst.z, m_pTransformCom->m_vPos.z, MAX_EPSILON))
	{
		m_bEnable = false;
		return;
	}

	// Dir
	m_vDir = m_vDst - m_pTransformCom->m_vPos;
	m_vDir.y = 0.0f;

	// Limit Speed
	if(D3DXVec3Length(&m_vDir) > m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime())
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_vDir = m_vDir * m_fSpeed * CTimeMgr::GetInstance()->GetDeltaTime();
	}

	// NextPos
	D3DXVECTOR3 vNextPos = m_pTransformCom->m_vPos + m_vDir;

	// Solution
	CNaviCell* pNextCell;
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pCell, &vNextPos, &pNextCell);

	// SetPos
	m_pTransformCom->m_vPos = vNextPos;

	// SetCell
	m_pCell = pNextCell;

	// Revision
	Revision();
}

void CPathFindCom::Render()
{
}

void CPathFindCom::Release()
{
	// Remove Group
	CPathFindMgr::GetInstance()->RemoveGroup(m_ePathType, m_pOwner);
}

bool CPathFindCom::Move(D3DXVECTOR3* _pDst)
{
	m_bEnable = true;
	m_vDst = *_pDst;
	return true;
}

bool CPathFindCom::Clear()
{
	m_bEnable = false;
	return true;
}

bool CPathFindCom::IsMove(D3DXVECTOR3* _pNextPos)
{
	*_pNextPos = m_vDst;
	return m_bEnable;
}

void CPathFindCom::Revision()
{
	// MapVec
	vector<CObject*> MapVec;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_MAP)->FindObjects(MapVec, _T("Map"));

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	// Variable
	CTransformCom* pMapTransformCom;
	CBufferCom* pMapBufferCom;
	CStaticMesh* pMapStaticMesh;
	IntersectInfo intersectInfo;
	D3DXVECTOR3 vDown = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	for(size_t i = 0; i < MapVec.size(); ++i)
	{
		// MapTransformCom
		pMapTransformCom = (CTransformCom*)MapVec[i]->GetComponent(COM_TYPE_TRANSFORM);

		// MapBufferCom
		pMapBufferCom = (CBufferCom*)MapVec[i]->GetComponent(COM_TYPE_BUFFER);

		// MapStaticMesh
		pMapStaticMesh = (CStaticMesh*)pMapBufferCom->m_BufferVec[0];

		// Intersect
		D3DXIntersect(pMapStaticMesh->m_pMesh, &(pTransformCom->m_vPos - pMapTransformCom->m_vPos + D3DXVECTOR3(0.0f, 50.0f, 0.0f)), &vDown, &intersectInfo.bHit, &intersectInfo.dwFaceIndex, &intersectInfo.u, &intersectInfo.v, &intersectInfo.dist, &intersectInfo.pBuffer, &intersectInfo.dwCountOfHits);

		// Is Hit??
		if(intersectInfo.bHit)
			pTransformCom->m_vPos += vDown * (intersectInfo.dist - 50.0f);
	}
}