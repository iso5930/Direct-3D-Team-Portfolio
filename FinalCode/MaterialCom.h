#pragma once

#include "Component.h"

class CMaterialCom : public CComponent
{
public:
	// Material
	D3DMATERIAL9* m_pMaterial;

	// Texture
	LPDIRECT3DBASETEXTURE9 m_pTexture;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMaterialCom(const D3DMATERIAL9* _pMaterial, TCHAR* _tszTexKey);
	virtual ~CMaterialCom();
};