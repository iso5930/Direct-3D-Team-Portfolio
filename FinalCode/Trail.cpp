#include "StdAfx.h"
#include "Trail.h"

CTrail::CTrail()
{
	// BufType
	m_eBufType = BUF_TYPE_TRAIL;

	// FVF
	m_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	// VtxSize
	m_dwVtxSize = sizeof(Vertex);

	// VtxCnt
	m_dwVtxCnt = 1000;

	CDeviceMgr::GetInstance()->GetDevice()->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, m_dwFVF, D3DPOOL_DEFAULT, &m_pVB, 0);
	m_pVS = new Vertex[m_dwVtxCnt];
}

CTrail::CTrail(CTrail* _pTrail)
{
	// BufType
	m_eBufType = BUF_TYPE_TRAIL;

	// RefCnt
	m_dwRefCnt = _pTrail->m_dwRefCnt + 1;

	// BufType
	m_eBufType = _pTrail->m_eBufType;

	// FVF
	m_dwFVF = _pTrail->m_dwFVF;

	// VtxSize
	m_dwVtxSize = _pTrail->m_dwVtxSize;

	// VtxCnt
	m_dwVtxCnt = _pTrail->m_dwVtxCnt;

	// IdxSize
	m_dwIdxSize = _pTrail->m_dwIdxSize;

	// TriCnt
	m_dwTriCnt = _pTrail->m_dwTriCnt;

	// VB
	m_pVB = _pTrail->m_pVB;

	// IB
	m_pIB = _pTrail->m_pIB;

	// VS
	m_pVS = _pTrail->m_pVS;

	// IS
	m_pIS = _pTrail->m_pIS;
}

CTrail::~CTrail()
{
}

int CTrail::Update()
{
	return 0;
}

void CTrail::Render()
{
	CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	CDeviceMgr::GetInstance()->GetDevice()->SetFVF(m_dwFVF);
	CDeviceMgr::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_dwTriCnt);
}

void CTrail::SetVB(Vertex* _pVS, DWORD _dwVtxCnt)
{
	// VtxCnt
	m_dwVtxCnt = _dwVtxCnt;

	// TriCnt
	m_dwTriCnt = _dwVtxCnt - 2;

	// VB
	Vertex* pVS;
	m_pVB->Lock(0, 0, (void**)&pVS, D3DLOCK_DISCARD);
	memcpy_s(pVS, m_dwVtxSize * m_dwVtxCnt, _pVS, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();

	// VS
	memcpy_s(m_pVS, m_dwVtxSize * m_dwVtxCnt, _pVS, m_dwVtxSize * m_dwVtxCnt);
}

CTrail* CTrail::Clone()
{
	return new CTrail(this);
}