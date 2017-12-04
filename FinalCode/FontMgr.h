#pragma once

class CFontMgr
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;

private:
	LPD3DXFONT m_pRomanFont[64][64];
	LPD3DXFONT m_pKostarFont[64][64];
	LPD3DXFONT m_pBauhaus[64][64];

public:
	LPD3DXFONT GetRomanFont(int _iHeight, int _iWidth);
	LPD3DXFONT GetKostarFont(int _iHeight, int _iWidth);
	LPD3DXFONT GetBauhaus(int _iHeight, int _iWidth);

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	DECLARE_SINGLETON(CFontMgr)

private:
	explicit CFontMgr();
	~CFontMgr();
};