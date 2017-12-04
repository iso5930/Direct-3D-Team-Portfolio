#include "Stdafx.h"
#include "DynamicMesh.h"

CDynamicMesh::CDynamicMesh()
{
	// BufType
	m_eBufType = BUF_TYPE_DYNAMIC_MESH;

	// Mode 0(Forward), 1(Backward), 2(Stop)
	m_iMode = 0;

	// Identity Matrix
	D3DXMatrixIdentity(&m_mIdentity);

	// Frame
	m_pRootFrame = NULL;

	// VTF
	m_pRootVTF = NULL;

	// Mesh Loader
	m_pMeshLoader = NULL;

	// Animation Controller
	m_pAnimController = NULL;
}

CDynamicMesh::CDynamicMesh(TCHAR* _tszPath, TCHAR* _tszFile)
{
	// BufType
	m_eBufType = BUF_TYPE_DYNAMIC_MESH;

	// Mode
	m_iMode = 0;

	// Identity Matrix
	D3DXMatrixIdentity(&m_mIdentity);

	// Frame
	m_pRootFrame = NULL;

	// VTF
	m_pRootVTF = NULL;

	// Mesh Loader
	m_pMeshLoader = NULL;

	// Animation Controller
	m_pAnimController = NULL;

	// FilePath
	TCHAR tszFilePath[MAX_STR];
	wsprintf(tszFilePath, _T("%s%s"), _tszPath, _tszFile);

	// Load
	m_pMeshLoader = new CMeshLoader(_tszPath, _tszFile);
	m_pAnimController = new CAnimController;

	if(FAILED(D3DXLoadMeshHierarchyFromX(tszFilePath, D3DXMESH_MANAGED, CDeviceMgr::GetInstance()->GetDevice(), m_pMeshLoader, NULL, &m_pRootFrame, &m_pAnimController->m_pAnimController)))
	{
		_tprintf(_T("D3DXLoadMeshHierarchyFromX() Error : %s\n"), tszFilePath);
		return;
	}

	// Setup Matrix Pointer
	SetupMatrixPointer((MeshFrame*)m_pRootFrame);

	// Setup VTF
	SetupVTF((MeshFrame*)m_pRootFrame, m_pRootVTF);
}

CDynamicMesh::~CDynamicMesh()
{
	// Animation Controller
	if(m_pAnimController != NULL)
		delete m_pAnimController;

	// VTF
	if(m_pRootVTF != NULL)
		delete m_pRootVTF;

	// RefCnt
	if(m_dwRefCnt != 0)
		return;

	// Mesh Loader
	if(m_pMeshLoader != NULL)
	{
		m_pMeshLoader->DestroyFrame(m_pRootFrame);
		delete m_pMeshLoader;
	}
}

int CDynamicMesh::Update()
{
	// Frame Move
	switch(m_iMode)
	{
	case 0:
		m_pAnimController->FrameMove(CTimeMgr::GetInstance()->GetDeltaTime());
		break;

	case 1:
		m_pAnimController->FrameMove(-CTimeMgr::GetInstance()->GetDeltaTime());
		break;

	case 2:
		m_pAnimController->FrameMove(0.0f);
		break;
	}

	// Update Matrix
	UpdateMatrix((MeshFrame*)m_pRootFrame, &m_mIdentity, m_pRootVTF);

	return 0;
}

void CDynamicMesh::Render()
{
}

CDynamicMesh* CDynamicMesh::Clone()
{
	CDynamicMesh* pClone = new CDynamicMesh;

	// RefCnt
	pClone->m_dwRefCnt = m_dwRefCnt + 1;

	// BufType
	pClone->m_eBufType = m_eBufType;

	// FVF
	pClone->m_dwFVF = m_dwFVF;

	// VtxSize
	pClone->m_dwVtxSize = m_dwVtxSize;

	// VtxCnt
	pClone->m_dwVtxCnt = m_dwVtxCnt;

	// IdxSize
	pClone->m_dwIdxSize = m_dwIdxSize;

	// TriCnt
	pClone->m_dwTriCnt = m_dwTriCnt;

	// Mode 0(Forward), 1(Backward), 2(Stop)
	pClone->m_iMode = m_iMode;

	// Identity Matrix
	memcpy_s(&pClone->m_mIdentity, sizeof(D3DXMATRIX), &m_mIdentity, sizeof(D3DXMATRIX));

	// Frame
	pClone->m_pRootFrame = m_pRootFrame;

	// VTF
	pClone->m_pRootVTF = NULL;

	// Mesh Loader
	pClone->m_pMeshLoader = m_pMeshLoader;

	// Animation Controller
	pClone->m_pAnimController = m_pAnimController->Clone();

	// Setup Matrix Pointer
	pClone->SetupVTF((MeshFrame*)pClone->m_pRootFrame, pClone->m_pRootVTF);

	return pClone;
}

void CDynamicMesh::UpdateMatrix(MeshFrame* _pMeshFrame, D3DXMATRIX* _pParentMatrix, SkinningVTF* _pSkinningVTF)
{
	// Update Matrix
	if(_pMeshFrame == NULL)
		return;

	// CombinedMatrix
	_pMeshFrame->mCombinedMatrix = _pMeshFrame->TransformationMatrix * (*_pParentMatrix);

	// Update VTF
	if(_pMeshFrame->pMeshContainer != NULL)
		UpdateVTF((MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	// Child UpdateMatrix
	if(_pMeshFrame->pFrameFirstChild != NULL)
		UpdateMatrix((MeshFrame*)_pMeshFrame->pFrameFirstChild, &_pMeshFrame->mCombinedMatrix, _pSkinningVTF->pFirstChild);

	// Sibling UpdateMatrix
	if(_pMeshFrame->pFrameSibling != NULL)
		UpdateMatrix((MeshFrame*)_pMeshFrame->pFrameSibling, _pParentMatrix, _pSkinningVTF->pSibling);
}

void CDynamicMesh::UpdateVTF(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pMeshContainer->pCombinationBuf->GetBufferPointer();
	DWORD dwNumBones = _pMeshContainer->pSkinInfo->GetNumBones();

	LPDIRECT3DTEXTURE9* ppTemp = _pSkinningVTF->ppPreVTF;
	_pSkinningVTF->ppPreVTF = _pSkinningVTF->ppCurVTF;
	_pSkinningVTF->ppCurVTF = ppTemp;

	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		for(DWORD j = 0; j < dwNumBones; ++j)
		{
			UINT iIndex = pBoneCombination[i].BoneId[j];
			if(iIndex <= 1000)
			{
				D3DXMatrixMultiply(&_pMeshContainer->pResultMatrix[j],
								   &_pMeshContainer->pOffsetMatrix[iIndex],
								   _pMeshContainer->ppCombinedMatrix[iIndex]);
			}
		}

		D3DLOCKED_RECT LockRect;
		_pSkinningVTF->ppCurVTF[i]->LockRect(0, &LockRect, NULL, 0);
		memcpy_s(LockRect.pBits, sizeof(D3DXMATRIX) * dwNumBones, _pMeshContainer->pResultMatrix, sizeof(D3DXMATRIX) * dwNumBones);
		_pSkinningVTF->ppCurVTF[i]->UnlockRect(0);
	}
}

void CDynamicMesh::SetupMatrixPointer(MeshFrame* _pMeshFrame)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL && _pMeshFrame->pMeshContainer->pSkinInfo != NULL)
	{
		// Num Bones
		DWORD dwNumFrames = _pMeshFrame->pMeshContainer->pSkinInfo->GetNumBones();

		// Mesh Container
		MeshContainer* pMeshContainer = (MeshContainer*)_pMeshFrame->pMeshContainer;

		// Create Combined Matrix
		pMeshContainer->ppCombinedMatrix = new D3DXMATRIX*[dwNumFrames];
		ZeroMemory(pMeshContainer->ppCombinedMatrix, sizeof(D3DXMATRIX*) * dwNumFrames);

		MeshFrame* pMeshFrame;
		for(DWORD i = 0; i < dwNumFrames; ++i)
		{
			// Find Frame
			pMeshFrame = (MeshFrame*)D3DXFrameFind(m_pRootFrame, pMeshContainer->pSkinInfo->GetBoneName(i));

			// Set Matrix Pointer
			pMeshContainer->ppCombinedMatrix[i] = &(pMeshFrame->mCombinedMatrix);
		}
	}

	// Child
	if(_pMeshFrame->pFrameFirstChild != NULL)
		SetupMatrixPointer((MeshFrame*)_pMeshFrame->pFrameFirstChild);

	// Sibling
	if(_pMeshFrame->pFrameSibling != NULL)
		SetupMatrixPointer((MeshFrame*)_pMeshFrame->pFrameSibling);
}

void CDynamicMesh::SetupVTF(MeshFrame* _pMeshFrame, SkinningVTF*& _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	_pSkinningVTF = new SkinningVTF;

	if(_pMeshFrame->pMeshContainer != NULL)
	{
		_pSkinningVTF->dwNumMaterials = _pMeshFrame->pMeshContainer->NumMaterials;
		_pSkinningVTF->ppCurVTF = new LPDIRECT3DTEXTURE9[_pSkinningVTF->dwNumMaterials];
		_pSkinningVTF->ppPreVTF = new LPDIRECT3DTEXTURE9[_pSkinningVTF->dwNumMaterials];

		for(DWORD i = 0; i < _pSkinningVTF->dwNumMaterials; ++i)
		{
			CDeviceMgr::GetInstance()->GetDevice()->CreateTexture(64, 64, 1, 0, D3DFMT_A32B32G32R32F, D3DPOOL_MANAGED, &_pSkinningVTF->ppCurVTF[i], NULL);
			CDeviceMgr::GetInstance()->GetDevice()->CreateTexture(64, 64, 1, 0, D3DFMT_A32B32G32R32F, D3DPOOL_MANAGED, &_pSkinningVTF->ppPreVTF[i], NULL);
		}
	}

	// Child
	if(_pMeshFrame->pFrameFirstChild != NULL)
		SetupVTF((MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	// Sibling
	if(_pMeshFrame->pFrameSibling != NULL)
		SetupVTF((MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}