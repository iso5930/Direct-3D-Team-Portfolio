#pragma once

#include "Buffer.h"

class CMeshLoader;
class CAnimController;

class CDynamicMesh : public CBuffer
{
public:
	// Mode 0(Forward), 1(Backward), 2(Stop)
	int m_iMode;

	// Identity Matrix
	D3DXMATRIX m_mIdentity;

	// Frame
	LPD3DXFRAME m_pRootFrame;

	// VTF
	SkinningVTF* m_pRootVTF;

	// Mesh Loader
	CMeshLoader* m_pMeshLoader;

	// Animation Controller
	CAnimController* m_pAnimController;

public:
	void UpdateMatrix(MeshFrame* _pMeshFrame, D3DXMATRIX* _pParentMatrix, SkinningVTF* _pSkinningVTF);
	void UpdateVTF(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF);
	void SetupMatrixPointer(MeshFrame* _pMeshFrame);
	void SetupVTF(MeshFrame* _pMeshFrame, SkinningVTF*& _pSkinningVTF);

public:
	virtual int Update();
	virtual void Render();
	virtual CDynamicMesh* Clone();

public:
	explicit CDynamicMesh();
	explicit CDynamicMesh(TCHAR* _tszPath, TCHAR* _tszFile);
	virtual ~CDynamicMesh();
};