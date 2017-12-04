#pragma once

#include "Buffer.h"

class CStaticMesh : public CBuffer
{
public:
	// Mesh
	LPD3DXMESH m_pMesh;

	// Subset
	LPD3DXBUFFER m_pSubset;

	// SubsetCnt
	DWORD m_dwSubsetCnt;

	// DiffuseTexture
	LPDIRECT3DTEXTURE9* m_ppDiffuseTexture;

	// NormalTexture
	LPDIRECT3DTEXTURE9* m_ppNormalTexture;

	// SpecularTexture
	LPDIRECT3DTEXTURE9* m_ppSpecularTexture;

	// Material
	D3DMATERIAL9* m_pMaterial;

public:
	virtual int Update();
	virtual void Render();
	virtual CStaticMesh* Clone();

public:
	explicit CStaticMesh();
	explicit CStaticMesh(TCHAR* _tszPath, TCHAR* _tszFile);
	virtual ~CStaticMesh();
};