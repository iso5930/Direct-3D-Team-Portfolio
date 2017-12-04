#include "Stdafx.h"
#include "Cube.h"

CCube::CCube()
{
	// BufType
	m_eBufType = BUF_TYPE_CUBE;

	// FVF
	m_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	// VtxSize
	m_dwVtxSize = sizeof(Vertex);

	// VtxCnt
	m_dwVtxCnt = 8;

	// IdxSize
	m_dwIdxSize = sizeof(Index);

	// TriCnt
	m_dwTriCnt = 12;

	CDeviceMgr::GetInstance()->GetDevice()->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0);
	CDeviceMgr::GetInstance()->GetDevice()->CreateIndexBuffer(m_dwTriCnt * m_dwIdxSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, 0);

	Vertex* pVS;
	m_pVB->Lock(0, 0, (void**)&pVS, 0);

	pVS[0].vPos.x = -0.5f;	pVS[0].vPos.y = -0.5f;	pVS[0].vPos.z = -0.5f;	pVS[0].vNormal.x = -0.57735f;	pVS[0].vNormal.y = -0.57735f;	pVS[0].vNormal.z = -0.57735f;	pVS[0].vTexUV.x = -0.5f;	pVS[0].vTexUV.y = -0.5f;	pVS[0].vTexUV.z = -0.5f;
	pVS[1].vPos.x = -0.5f;	pVS[1].vPos.y = 0.5f;	pVS[1].vPos.z = -0.5f;	pVS[1].vNormal.x = -0.57735f;	pVS[1].vNormal.y = 0.57735f;	pVS[1].vNormal.z = -0.57735f;	pVS[1].vTexUV.x = -0.5f;	pVS[1].vTexUV.y = 0.5f;		pVS[1].vTexUV.z = -0.5f;
	pVS[2].vPos.x = 0.5f;	pVS[2].vPos.y = 0.5f;	pVS[2].vPos.z = -0.5f;	pVS[2].vNormal.x = 0.57735f;	pVS[2].vNormal.y = 0.57735f;	pVS[2].vNormal.z = -0.57735f;	pVS[2].vTexUV.x = 0.5f;		pVS[2].vTexUV.y = 0.5f;		pVS[2].vTexUV.z = -0.5f;
	pVS[3].vPos.x = 0.5f;	pVS[3].vPos.y = -0.5f;	pVS[3].vPos.z = -0.5f;	pVS[3].vNormal.x = 0.57735f;	pVS[3].vNormal.y = -0.57735f;	pVS[3].vNormal.z = -0.57735f;	pVS[3].vTexUV.x = 0.5f;		pVS[3].vTexUV.y = -0.5f;	pVS[3].vTexUV.z = -0.5f;
	pVS[4].vPos.x = -0.5f;	pVS[4].vPos.y = -0.5f;	pVS[4].vPos.z = 0.5f;	pVS[4].vNormal.x = -0.57735f;	pVS[4].vNormal.y = -0.57735f;	pVS[4].vNormal.z = 0.57735f;	pVS[4].vTexUV.x = -0.5f;	pVS[4].vTexUV.y = -0.5f;	pVS[4].vTexUV.z = 0.5f;
	pVS[5].vPos.x = -0.5f;	pVS[5].vPos.y = 0.5f;	pVS[5].vPos.z = 0.5f;	pVS[5].vNormal.x = -0.57735f;	pVS[5].vNormal.y = 0.57735f;	pVS[5].vNormal.z = 0.57735f;	pVS[5].vTexUV.x = -0.5f;	pVS[5].vTexUV.y = 0.5f;		pVS[5].vTexUV.z = 0.5f;
	pVS[6].vPos.x = 0.5f;	pVS[6].vPos.y = 0.5f;	pVS[6].vPos.z = 0.5f;	pVS[6].vNormal.x = 0.57735f;	pVS[6].vNormal.y = 0.57735f;	pVS[6].vNormal.z = 0.57735f;	pVS[6].vTexUV.x = 0.5f;		pVS[6].vTexUV.y = 0.5f;		pVS[6].vTexUV.z = 0.5f;
	pVS[7].vPos.x = 0.5f;	pVS[7].vPos.y = -0.5f;	pVS[7].vPos.z = 0.5f;	pVS[7].vNormal.x = 0.57735f;	pVS[7].vNormal.y = -0.57735f;	pVS[7].vNormal.z = 0.57735f;	pVS[7].vTexUV.x = 0.5f;		pVS[7].vTexUV.y = -0.5f;	pVS[7].vTexUV.z = 0.5f;

	m_pVS = new Vertex[m_dwVtxCnt];
	memcpy_s(m_pVS, m_dwVtxSize * m_dwVtxCnt, pVS, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();

	Index* pIS;
	m_pIB->Lock(0, 0, (void**)&pIS, 0);

	pIS[0]._1 = 0;	pIS[0]._2  = 1;	pIS[0]._3  = 2;
	pIS[1]._1 = 0;	pIS[1]._2  = 2;	pIS[1]._3  = 3;
	pIS[2]._1 = 4;	pIS[2]._2  = 6;	pIS[2]._3  = 5;
	pIS[3]._1 = 4;	pIS[3]._2 = 7;	pIS[3]._3 = 6;
	pIS[4]._1 = 4;	pIS[4]._2 = 5;	pIS[4]._3 = 1;
	pIS[5]._1 = 4;	pIS[5]._2 = 1;	pIS[5]._3 = 0;
	pIS[6]._1 = 3;	pIS[6]._2 = 2;	pIS[6]._3 = 6;
	pIS[7]._1 = 3;	pIS[7]._2 = 6;	pIS[7]._3 = 7;
	pIS[8]._1 = 1;	pIS[8]._2 = 5;	pIS[8]._3 = 6;
	pIS[9]._1 = 1;	pIS[9]._2 = 6;	pIS[9]._3 = 2;
	pIS[10]._1 = 4;	pIS[10]._2 = 0; pIS[10]._3 = 3;
	pIS[11]._1 = 4;	pIS[11]._2 = 3; pIS[11]._3 = 7;

	m_pIS = new Index[m_dwTriCnt];
	memcpy_s(m_pIS, m_dwIdxSize * m_dwTriCnt, pIS, m_dwIdxSize * m_dwTriCnt);
	m_pIB->Unlock();
}

CCube::CCube(CCube* _pCube)
{
	// BufType
	m_eBufType = BUF_TYPE_CUBE;

	// RefCnt
	m_dwRefCnt = _pCube->m_dwRefCnt + 1;

	// BufType
	m_eBufType = _pCube->m_eBufType;

	// FVF
	m_dwFVF = _pCube->m_dwFVF;

	// VtxSize
	m_dwVtxSize = _pCube->m_dwVtxSize;

	// VtxCnt
	m_dwVtxCnt = _pCube->m_dwVtxCnt;

	// IdxSize
	m_dwIdxSize = _pCube->m_dwIdxSize;

	// TriCnt
	m_dwTriCnt = _pCube->m_dwTriCnt;

	// VB
	m_pVB = _pCube->m_pVB;

	// IB
	m_pIB = _pCube->m_pIB;

	// VS
	m_pVS = _pCube->m_pVS;

	// IS
	m_pIS = _pCube->m_pIS;
}

CCube::~CCube()
{
}

int CCube::Update()
{
	return 0;
}

void CCube::Render()
{
	CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	CDeviceMgr::GetInstance()->GetDevice()->SetIndices(m_pIB);
	CDeviceMgr::GetInstance()->GetDevice()->SetFVF(m_dwFVF);
	CDeviceMgr::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

CCube* CCube::Clone()
{
	return new CCube(this);
}