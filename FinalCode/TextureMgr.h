#pragma once

class CTextureMgr
{
private:
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9> m_TextureMap;

public:
	void AddTexture(TCHAR* _tszTexKey, LPDIRECT3DBASETEXTURE9 _pTexture);
	void RemoveTexture(TCHAR* _tszTexKey);
	LPDIRECT3DBASETEXTURE9 GetTexture(TCHAR* _tszTexKey);

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	DECLARE_SINGLETON(CTextureMgr)

private:
	explicit CTextureMgr();
	~CTextureMgr();
};