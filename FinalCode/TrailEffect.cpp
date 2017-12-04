#include "StdAfx.h"
#include "TrailEffect.h"

CTrailEffect::CTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwMaxCnt, D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown, float _fPeriod, TCHAR* _tszTexKey)
: CObject(_tszObjKey, _eObjType)
{
	// Vertex
	m_pVertex = new Vertex[_dwMaxCnt];

	// Cnt
	m_dwCnt = 0;

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
}

CTrailEffect::~CTrailEffect()
{
	Release();
}

void CTrailEffect::Initialize()
{
	CObject::Initialize();
}

int CTrailEffect::Update()
{
	CObject::Update();

	return 0;
}

void CTrailEffect::Render()
{
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

void CTrailEffect::Release()
{
	delete[] m_pVertex;
}

void CTrailEffect::Add(D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown)
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