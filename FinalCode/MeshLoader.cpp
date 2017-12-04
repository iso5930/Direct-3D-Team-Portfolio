#include "Stdafx.h"
#include "MeshLoader.h"

CMeshLoader::CMeshLoader(TCHAR* _tszPath, TCHAR* _tszFile)
{
	// Device
	m_pDevice = CDeviceMgr::GetInstance()->GetDevice();

	// Path
	_tcscpy_s(m_tszPath, MAX_STR, _tszPath);

	// File
	_tcscpy_s(m_tszFile, MAX_STR, _tszFile);
}

CMeshLoader::~CMeshLoader()
{
}

STDMETHODIMP CMeshLoader::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	// Mesh Frame
	MeshFrame* pMeshFrame = new MeshFrame;
	ZeroMemory(pMeshFrame, sizeof(MeshFrame));

	// Name
	if(Name != NULL)
	{
		int iLen = strlen(Name);
		pMeshFrame->Name = new char[iLen + 1];
		strcpy_s(pMeshFrame->Name, iLen + 1, Name);
	//	cout << pMeshFrame->Name << endl;
	}

	// Identity
	D3DXMATRIX mIdentity;
	D3DXMatrixIdentity(&mIdentity);

	// Set
	pMeshFrame->mCombinedMatrix = pMeshFrame->TransformationMatrix = mIdentity;
	*ppNewFrame = pMeshFrame;

	return S_OK;
}

STDMETHODIMP CMeshLoader::CreateMeshContainer(THIS_ LPCSTR Name
											  , CONST D3DXMESHDATA *pMeshData							
											  , CONST D3DXMATERIAL *pMaterials
											  , CONST D3DXEFFECTINSTANCE *pEffectInstances
											  , DWORD NumMaterials
											  , CONST DWORD *pAdjacency
											  , LPD3DXSKININFO pSkinInfo
											  , LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	// Mesh
	LPD3DXMESH pMesh = pMeshData->pMesh;
	if(pMesh->GetFVF() == 0)
	{
		cout << "GetFVF() Error" << endl;
		return E_FAIL;
	}

	// Mesh Container
	MeshContainer* pMeshContainer = new MeshContainer;
	ZeroMemory(pMeshContainer, sizeof(MeshContainer));

	pMeshContainer->pMesh = pMeshData->pMesh;
	pMeshContainer->MeshData.pMesh = pMeshData->pMesh;
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	// Name
	if(NULL != Name)
	{
		int iLen = strlen(Name);
		pMeshContainer->Name = new char[iLen + 1];
		strcpy_s(pMeshContainer->Name, iLen + 1, Name);
	}

	// Adjacency
	DWORD dwNumFaces = pMesh->GetNumFaces();
	pMeshContainer->pAdjacency = new DWORD[dwNumFaces * 3];
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwNumFaces * 3);

	// Normal Vector
	if(pMesh->GetFVF() & D3DFVF_NORMAL)
	{
		if(FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), m_pDevice, &pMeshContainer->MeshData.pMesh)))
		{
			cout << "CloneMeshFVF() Error" << endl;
			return E_FAIL;
		}

		pMesh->AddRef();
	}
	else
	{
		if(FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, m_pDevice, &pMeshContainer->MeshData.pMesh)))
		{
			cout << "CloneMeshFVF() Error" << endl;
			return E_FAIL;
		}

		D3DXComputeNormals(pMeshContainer->MeshData.pMesh, pMeshContainer->pAdjacency);
	}

	// Material
	pMeshContainer->NumMaterials = max(NumMaterials, 1);

	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppDiffuseTexture =new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->ppNormalTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->ppSpecularTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);
	ZeroMemory(pMeshContainer->ppDiffuseTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	ZeroMemory(pMeshContainer->ppNormalTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	ZeroMemory(pMeshContainer->ppSpecularTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	TCHAR tszTexPath[MAX_STR], tszTexture[MAX_STR];
	if(NumMaterials > 0)
	{
		memcpy_s(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * NumMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for(DWORD i = 0; i < NumMaterials; ++i)
		{
			if(pMeshContainer->pMaterials[i].pTextureFilename == NULL)
				continue;

			ZeroMemory(tszTexture, sizeof(tszTexture));
			MultiByteToWideChar(CP_ACP, 0, pMeshContainer->pMaterials[i].pTextureFilename, strlen(pMeshContainer->pMaterials[i].pTextureFilename), tszTexture, MAX_STR);

			// Diffuse Texture
			wsprintf(tszTexPath, _T("%s%s"), m_tszPath, tszTexture);
			if(FAILED(D3DXCreateTextureFromFile(m_pDevice, tszTexPath, &pMeshContainer->ppDiffuseTexture[i])))
			{
				cout << "D3DXCreateTextureFromFile() Error" << endl;
				return E_FAIL;
			}

			int iDot;

			// Normal Texture
			wsprintf(tszTexPath, _T("%s%s"), m_tszPath, tszTexture);

			// Find Dot
			iDot = _tcslen(tszTexPath);
			while(--iDot)
			{
				if(tszTexPath[iDot] == _T('.'))
				{
					tszTexPath[iDot] = NULL;
					break;
				}
			}

			_tcscat_s(tszTexPath, MAX_STR, _T("_NRM.dds"));
			if(FAILED(D3DXCreateTextureFromFile(m_pDevice, tszTexPath, &pMeshContainer->ppNormalTexture[i])))
			{
				cout << "D3DXCreateTextureFromFile() Error" << endl;
				return E_FAIL;
			}

			// Specular
			wsprintf(tszTexPath, _T("%s%s"), m_tszPath, tszTexture);

			// Find Dot
			iDot = _tcslen(tszTexPath);
			while(--iDot)
			{
				if(tszTexPath[iDot] == _T('.'))
				{
					tszTexPath[iDot] = NULL;
					break;
				}
			}

			_tcscat_s(tszTexPath, MAX_STR, _T("_SPEC.dds"));
			if(FAILED(D3DXCreateTextureFromFile(m_pDevice, tszTexPath, &pMeshContainer->ppSpecularTexture[i])))
			{
				cout << "D3DXCreateTextureFromFile() Error" << endl;
				return E_FAIL;
			}
		}
	}
	else
	{
		ZeroMemory(&pMeshContainer->pMaterials[0].MatD3D, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.a = 1.f;
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
	}

	// Skin Info
	if(pSkinInfo != NULL)
	{
		// Skin Info
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		// Convert Index Blended Mesh
		DWORD numBoneComboEntries = 0;

		pSkinInfo->ConvertToIndexedBlendedMesh(pMeshData->pMesh,
			D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
			64, pAdjacency, pMeshContainer->pAdjacency, NULL, NULL,
			&pMeshContainer->dwMaxVertexInfl,
			&numBoneComboEntries,
			&pMeshContainer->pCombinationBuf,
			&pMeshContainer->MeshData.pMesh);

		// NumBones
		DWORD dwNumBones = pMeshContainer->pSkinInfo->GetNumBones();

		pMeshContainer->pOffsetMatrix = new D3DXMATRIX[dwNumBones];
		ZeroMemory(pMeshContainer->pOffsetMatrix, sizeof(D3DXMATRIX) * dwNumBones);

		pMeshContainer->pResultMatrix = new D3DXMATRIX[dwNumBones];
		ZeroMemory(pMeshContainer->pResultMatrix, sizeof(D3DXMATRIX) * dwNumBones);

		for(DWORD i = 0; i < dwNumBones; ++i)
			memcpy_s(&(pMeshContainer->pOffsetMatrix[i]), sizeof(D3DXMATRIX), pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DXMATRIX));
	}
	else
	{
		pMeshContainer->pSkinInfo = NULL;
		pMeshContainer->pMesh = NULL;
		pMeshContainer->pOffsetMatrix = NULL;
	}

	// Optimize
	if(pMeshContainer->pMesh->GetNumFaces() > 0)
	{
		DWORD* pAdjacency = new DWORD[pMeshContainer->pMesh->GetNumFaces() * 3];
		pMeshContainer->pMesh->GenerateAdjacency(0.0f, pAdjacency);
		pMeshContainer->pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, pAdjacency, NULL, NULL, NULL);
		delete[] pAdjacency;
	}

	*ppNewMeshContainer = pMeshContainer;

	return S_OK;
}

STDMETHODIMP CMeshLoader::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	if(pFrameToFree == NULL)
	{
		cout << "DestroyFrame() Error" << endl;
		return E_FAIL;
	}

	// Mesh Container
	if(pFrameToFree->pMeshContainer != NULL)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	// Child
	if(pFrameToFree->pFrameFirstChild != NULL)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	// Sibling
	if(pFrameToFree->pFrameSibling != NULL)
		DestroyFrame(pFrameToFree->pFrameSibling);

	// Name
	if(pFrameToFree->Name != NULL)
		delete[] pFrameToFree->Name;

	// Frame
	delete pFrameToFree;

	return S_OK;
}

STDMETHODIMP CMeshLoader::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	// Casting
	MeshContainer* pMeshContainer = (MeshContainer*)pMeshContainerToFree;

	// Texture
	for(DWORD i = 0; i < pMeshContainerToFree->NumMaterials; ++i)
	{
		if(pMeshContainer->ppDiffuseTexture[i] != NULL)
			pMeshContainer->ppDiffuseTexture[i]->Release();
		if(pMeshContainer->ppNormalTexture[i] != NULL)
			pMeshContainer->ppNormalTexture[i]->Release();
		if(pMeshContainer->ppSpecularTexture[i] != NULL)
			pMeshContainer->ppSpecularTexture[i]->Release();
	}

	if(pMeshContainer->ppDiffuseTexture != NULL)
	{
		delete[] pMeshContainer->ppDiffuseTexture;
		delete[] pMeshContainer->ppNormalTexture;
		delete[] pMeshContainer->ppSpecularTexture;
	}

	// Material
	if(pMeshContainer->pMaterials)
		delete[] pMeshContainer->pMaterials;

	// Name
	if(pMeshContainer->Name)
		delete[] pMeshContainer->Name;

	// Offset Matrix
	if(pMeshContainer->pOffsetMatrix)
		delete[] pMeshContainer->pOffsetMatrix;

	// Combined Matrix
	if(pMeshContainer->ppCombinedMatrix)
		delete[] pMeshContainer->ppCombinedMatrix;

	// Result Matrix
	if(pMeshContainer->pResultMatrix)
		delete[] pMeshContainer->pResultMatrix;

	// Adjacency
	if(pMeshContainer->pAdjacency)
		delete[] pMeshContainer->pAdjacency;

	// Mesh
	if(pMeshContainer->pMesh != NULL)
		pMeshContainer->pMesh->Release();

	// Mesh Data
	if(pMeshContainer->MeshData.pMesh != NULL)
		pMeshContainer->MeshData.pMesh->Release();

	// Skin Info
	if(pMeshContainer->pSkinInfo != NULL)
		pMeshContainer->pSkinInfo->Release();

	// Combination Buf
	if(pMeshContainer->pCombinationBuf != NULL)
		pMeshContainer->pCombinationBuf->Release();

	// Mesh Container
	if(pMeshContainer != NULL)
		delete pMeshContainer;

	return S_OK;
}