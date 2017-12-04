#pragma once

class CRenderTarget
{
public:
	LPDIRECT3DTEXTURE9 m_pTexture;

private:
	bool m_bUse;
	D3DXCOLOR m_dwColor;

	LPDIRECT3DSURFACE9 m_pSurface;
	LPDIRECT3DSURFACE9 m_pDepthStencil;

	LPDIRECT3DSURFACE9 m_pBackSurface;
	LPDIRECT3DSURFACE9 m_pBackDepthStencil;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

public:
	void Clear();
	void Begin(DWORD _dwIndex);
	void End(DWORD _dwIndex);

public:
	void CreateDebugBuffer(float _fX, float _fY, float _fSizeX, float _fSizeY);
	void RenderDebugBuffer();

public:
	explicit CRenderTarget(DWORD _dwSizeX, DWORD _dwSizeY, D3DFORMAT _Format, D3DXCOLOR _dwColor);
	~CRenderTarget();
};
