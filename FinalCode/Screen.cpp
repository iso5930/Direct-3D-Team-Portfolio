#include "Stdafx.h"
#include "Screen.h"

CScreen::CScreen()
{
	// BufType
	m_eBufType = BUF_TYPE_SCREEN;

	// FVF
	m_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	// VtxSize
	m_dwVtxSize = sizeof(Vertex);

	// VtxCnt
	m_dwVtxCnt = 4;

	// IdxSize
	m_dwIdxSize = sizeof(Index);

	// TriCnt
	m_dwTriCnt = 2;

	CDeviceMgr::GetInstance()->GetDevice()->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0);
	CDeviceMgr::GetInstance()->GetDevice()->CreateIndexBuffer(m_dwTriCnt * m_dwIdxSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, 0);

	Vertex* pVS;
	m_pVB->Lock(0, 0, (void**)&pVS, 0);

	pVS[0].vPos.x = -1.0f;		pVS[0].vPos.y = -1.0f;		pVS[0].vPos.z = 0.0f;		pVS[0].vNormal.x = 0.0f;	pVS[0].vNormal.y = 0.0f;	pVS[0].vNormal.z = -1.0f;	pVS[0].vTexUV.x = 0.0f;		pVS[0].vTexUV.y = 1.0f;
	pVS[1].vPos.x = -1.0f;		pVS[1].vPos.y = 1.0f;		pVS[1].vPos.z = 0.0f;		pVS[1].vNormal.x = 0.0f;	pVS[1].vNormal.y = 0.0f;	pVS[1].vNormal.z = -1.0f;	pVS[1].vTexUV.x = 0.0f;		pVS[1].vTexUV.y = 0.0f;
	pVS[2].vPos.x = 1.0f;		pVS[2].vPos.y = 1.0f;		pVS[2].vPos.z = 0.0f;		pVS[2].vNormal.x = 0.0f;	pVS[2].vNormal.y = 0.0f;	pVS[2].vNormal.z = -1.0f;	pVS[2].vTexUV.x = 1.0f;		pVS[2].vTexUV.y = 0.0f;
	pVS[3].vPos.x = 1.0f;		pVS[3].vPos.y = -1.0f;		pVS[3].vPos.z = 0.0f;		pVS[3].vNormal.x = 0.0f;	pVS[3].vNormal.y = 0.0f;	pVS[3].vNormal.z = -1.0f;	pVS[3].vTexUV.x = 1.0f;		pVS[3].vTexUV.y = 1.0f;

	m_pVS = new Vertex[m_dwVtxCnt];
	memcpy_s(m_pVS, m_dwVtxSize * m_dwVtxCnt, pVS, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();

	Index* pIS;
	m_pIB->Lock(0, 0, (void**)&pIS, 0);
	pIS[0]._1 = 0;		pIS[0]._2 = 1;		pIS[0]._3 = 2;
	pIS[1]._1 = 0;		pIS[1]._2 = 2;		pIS[1]._3 = 3;

	m_pIS = new Index[m_dwTriCnt];
	memcpy_s(m_pIS, m_dwIdxSize * m_dwTriCnt, pIS, m_dwIdxSize * m_dwTriCnt);
	m_pIB->Unlock();
}

CScreen::CScreen(CScreen* _pScreen)
{
	// BufType
	m_eBufType = BUF_TYPE_SCREEN;

	// RefCnt
	m_dwRefCnt = _pScreen->m_dwRefCnt + 1;

	// BufType
	m_eBufType = _pScreen->m_eBufType;

	// FVF
	m_dwFVF = _pScreen->m_dwFVF;

	// VtxSize
	m_dwVtxSize = _pScreen->m_dwVtxSize;

	// VtxCnt
	m_dwVtxCnt = _pScreen->m_dwVtxCnt;

	// IdxSize
	m_dwIdxSize = _pScreen->m_dwIdxSize;

	// TriCnt
	m_dwTriCnt = _pScreen->m_dwTriCnt;

	// VB
	m_pVB = _pScreen->m_pVB;

	// IB
	m_pIB = _pScreen->m_pIB;

	// VS
	m_pVS = _pScreen->m_pVS;

	// IS
	m_pIS = _pScreen->m_pIS;
}

CScreen::~CScreen()
{
}

int CScreen::Update()
{
	return 0;
}

void CScreen::Render()
{
	CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	CDeviceMgr::GetInstance()->GetDevice()->SetIndices(m_pIB);
	CDeviceMgr::GetInstance()->GetDevice()->SetFVF(m_dwFVF);
	CDeviceMgr::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

CScreen* CScreen::Clone()
{
	return new CScreen(this);
}