#include "StdAfx.h"
#include "TrailEffect_3.h"

CTrailEffect_3::CTrailEffect_3(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwMaxCnt, D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown, float _fPeriod, TCHAR* _tszTexKey, DWORD _dwStartCnt, D3DXVECTOR3 _vDir)
:CObject(_tszObjKey, _eObjType)
{
	// Vertex
	m_pVertex = new Vertex[_dwMaxCnt];

	// Cnt
	m_dwCnt = 0;

	m_dwStartCnt = _dwStartCnt;

	// MaxCnt
	m_dwMaxCnt = _dwMaxCnt;

	// Matrix
	m_pMatrix = _pMatrix;

	// Up
	m_vUp = *_pUp;

	// Down
	m_vDown = *_pDown;

	// Period
	m_fPeriod = _fPeriod;

	// Time
	m_fTime = 0.0f;

	// BufferCom
	m_pBufferCom = new CBufferCom;
	m_pBufferCom->AddBuffer(_T("Trail"));
	AddComponent(m_pBufferCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _tszTexKey);
	AddComponent(pMaterialCom);

	// TrailMesh
	m_pTrail = (CTrail*)m_pBufferCom->m_BufferVec[0];

	m_vDir = _vDir;
}

CTrailEffect_3::~CTrailEffect_3(void)
{
	Release();
}	

void CTrailEffect_3::Initialize()
{
	CObject::Initialize();

	float fDist = 200.f;

	for(DWORD i = 0; i <= m_dwStartCnt; ++i)
	{
		//여기서 생성을 해야하는데...
		D3DXVECTOR3 vDir = m_vDir * -1;

		D3DXVECTOR3 vUp, vDown;
		D3DXVec3TransformCoord(&vUp, &m_vUp, m_pMatrix);
		D3DXVec3TransformCoord(&vDown, &m_vDown, m_pMatrix);

		vUp += vDir * fDist;
		vDown += vDir * fDist;
		
		Add(&vUp, &vDown);

		fDist -= 5.f;
	}
}

int CTrailEffect_3::Update()
{
	CObject::Update();

	return 0;
}

void CTrailEffect_3::Render()
{
	CObject::Render();

	CObject::Render();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > m_fPeriod)
	{
		m_fTime = 0.0f;

		D3DXVECTOR3 vUp, vDown;
		D3DXVec3TransformCoord(&vUp, &m_vUp, m_pMatrix);
		D3DXVec3TransformCoord(&vDown, &m_vDown, m_pMatrix);

		Add(&vUp, &vDown);
	}

	if(m_dwCnt < 2)
		return;

	for(size_t i = 0; i < m_dwCnt; ++i)
	{
		m_pVertex[i].vTexUV.x = 1.0f - (float(i / 2) / float(m_dwCnt / 2 - 1));
		m_pVertex[i].vTexUV.y = float(i % 2);
	}

	// SetVS
	m_pTrail->SetVB(m_pVertex, m_dwCnt);
}

void CTrailEffect_3::Release()
{
	delete[] m_pVertex;
}

void CTrailEffect_3::Add(D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown)
{
	if(m_dwMaxCnt == m_dwCnt)
	{
		for(size_t i = 2; i < m_dwMaxCnt; ++i)
			m_pVertex[i - 2] = m_pVertex[i];
	}
	else
		m_dwCnt += 2;

	m_pVertex[m_dwCnt - 2].vPos = *_pUp;
	m_pVertex[m_dwCnt - 1].vPos = *_pDown;
}