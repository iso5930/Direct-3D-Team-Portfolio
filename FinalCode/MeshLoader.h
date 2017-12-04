#pragma once

class CMeshLoader : public ID3DXAllocateHierarchy
{
private:
	// Device
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	// Path
	TCHAR m_tszPath[MAX_STR];

	// File
	TCHAR m_tszFile[MAX_STR];

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

public:
	explicit CMeshLoader(TCHAR* _tszPath, TCHAR* _tszFile);
	~CMeshLoader();
};