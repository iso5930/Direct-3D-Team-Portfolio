#pragma once

class CBuffer
{
protected:
	// RefCnt
	DWORD m_dwRefCnt;

public:
	// BufType
	BUF_TYPE m_eBufType;

	// FVF
	DWORD m_dwFVF;

	// VtxSize
	DWORD m_dwVtxSize;

	// VtxCnt
	DWORD m_dwVtxCnt;

	// IdxSize
	DWORD m_dwIdxSize;

	// TriCnt
	DWORD m_dwTriCnt;

	// VB
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	// IB
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	// VS
	Vertex* m_pVS;

	// IS
	Index* m_pIS;

public:
	virtual int Update() = 0;
	virtual void Render() = 0;
	virtual CBuffer* Clone() = 0;

public:
	virtual void SetVB(Vertex* _pVS, DWORD _dwVtxCnt);
	virtual void SetIB(Index* _pIS, DWORD _dwTriCnt);

public:
	explicit CBuffer();
	virtual ~CBuffer();
};
