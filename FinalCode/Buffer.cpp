#include "StdAfx.h"
#include "Buffer.h"

CBuffer::CBuffer()
{
	// BufType
	m_eBufType = BUF_TYPE_END;

	// RefCnt
	m_dwRefCnt = 0;

	// FVF
	m_dwFVF = 0;

	// VtxSize
	m_dwVtxSize = 0;

	// VtxCnt
	m_dwVtxCnt = 0;

	// IdxSize
	m_dwIdxSize = 0;

	// TriCnt
	m_dwTriCnt = 0;

	// VB
	m_pVB = NULL;

	// IB
	m_pIB = NULL;

	// VS
	m_pVS = NULL;

	// IS
	m_pIS = NULL;
}

CBuffer::~CBuffer()
{
	if(m_dwRefCnt != 0)
		return;

	if(m_pVB != NULL)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}

	if(m_pIB != NULL)
	{
		m_pIB->Release();
		m_pIB = NULL;
	}

	if(m_pVS != NULL)
	{
		delete[] m_pVS;
		m_pVS = NULL;
	}

	if(m_pIS != NULL)
	{
		delete[] m_pIS;
		m_pIS = NULL;
	}
}

void CBuffer::SetVB(Vertex* _pVS, DWORD _dwVtxCnt)
{
	Vertex* pVS;
	m_pVB->Lock(0, 0, (void**)&pVS, 0);
	memcpy_s(pVS, m_dwVtxSize * m_dwVtxCnt, _pVS, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();

	memcpy_s(m_pVS, m_dwVtxSize * m_dwVtxCnt, _pVS, m_dwVtxSize * m_dwVtxCnt);
}

void CBuffer::SetIB(Index* _pIS, DWORD _dwTriCnt)
{
	Index* pIS;
	m_pIB->Lock(0, 0, (void**)&pIS, 0);
	memcpy_s(pIS, m_dwVtxSize * m_dwTriCnt, _pIS, m_dwIdxSize * m_dwTriCnt);
	m_pIB->Unlock();

	memcpy_s(m_pIS, m_dwVtxSize * m_dwTriCnt, _pIS, m_dwIdxSize * m_dwTriCnt);
}