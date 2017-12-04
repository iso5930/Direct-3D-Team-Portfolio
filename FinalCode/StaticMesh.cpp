#include "Stdafx.h"
#include "StaticMesh.h"

CStaticMesh::CStaticMesh()
{
	// BufType
	m_eBufType = BUF_TYPE_STATIC_MESH;

	// Mesh
	m_pMesh = NULL;

	// Subset
	m_pSubset = NULL;

	// SubsetCnt
	m_dwSubsetCnt = 0;

	// DiffuseTexture
	m_ppDiffuseTexture = NULL;

	// NormalTexture
	m_ppNormalTexture = NULL;

	// SpecularTexture
	m_ppSpecularTexture = NULL;

	// Material
	m_pMaterial = NULL;
}

CStaticMesh::CStaticMesh(TCHAR* _tszPath, TCHAR* _tszFile)
{
	// FilePath
	TCHAR tszFilePath[MAX_STR];
	wsprintf(tszFilePath, _T("%s%s"), _tszPath, _tszFile);

	// LoadMesh
	if(FAILED(D3DXLoadMeshFromX(tszFilePath, D3DXMESH_MANAGED, CDeviceMgr::GetInstance()->GetDevice(), NULL, &m_pSubset, NULL, &m_dwSubsetCnt, &m_pMesh)))
	{
		_tprintf(_T("D3DXLoadMeshFromX() Error : %s\n"), tszFilePath);
		return;
	}

	D3DXMATERIAL* pSubset = (D3DXMATERIAL*)m_pSubset->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwSubsetCnt];
	m_ppDiffuseTexture = new LPDIRECT3DTEXTURE9[m_dwSubsetCnt];		ZeroMemory(m_ppDiffuseTexture, sizeof(LPDIRECT3DTEXTURE9) * m_dwSubsetCnt);
	m_ppNormalTexture = new LPDIRECT3DTEXTURE9[m_dwSubsetCnt];		ZeroMemory(m_ppNormalTexture, sizeof(LPDIRECT3DTEXTURE9) * m_dwSubsetCnt);
	m_ppSpecularTexture = new LPDIRECT3DTEXTURE9[m_dwSubsetCnt];	ZeroMemory(m_ppSpecularTexture, sizeof(LPDIRECT3DTEXTURE9) * m_dwSubsetCnt);

	TCHAR tszTexture[MAX_STR], tszTexPath[MAX_STR];

	for(DWORD i = 0; i < m_dwSubsetCnt; ++i)
	{
		if(pSubset[i].pTextureFilename == NULL)
			continue;

		// TexName
		ZeroMemory(tszTexture, sizeof(tszTexture));
		MultiByteToWideChar(CP_ACP, 0, pSubset[i].pTextureFilename, strlen(pSubset[i].pTextureFilename), tszTexture, MAX_STR);
		
		// Diffuse
		ZeroMemory(tszTexPath, sizeof(tszTexPath));
		wsprintf(tszTexPath, _T("%s%s"), _tszPath, tszTexture);
		if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), tszTexPath, &m_ppDiffuseTexture[i])))
		{
			_tprintf(_T("D3DXCreateTextureFromFile() Error : %s\n"), tszTexPath);
			break;
		}

		int iDot;

		// Normal
		ZeroMemory(tszTexPath, sizeof(tszTexPath));
		wsprintf(tszTexPath, _T("%s%s"), _tszPath, tszTexture);

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
		if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), tszTexPath, &m_ppNormalTexture[i])))
		{
			_tprintf(_T("D3DXCreateTextureFromFile() Error : %s\n"), tszTexPath);
			break;
		}

		// Specular
		ZeroMemory(tszTexPath, sizeof(tszTexPath));
		wsprintf(tszTexPath, _T("%s%s"), _tszPath, tszTexture);

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
		if(FAILED(D3DXCreateTextureFromFile(CDeviceMgr::GetInstance()->GetDevice(), tszTexPath, &m_ppSpecularTexture[i])))
		{
			_tprintf(_T("D3DXCreateTextureFromFile() Error : %s\n"), tszTexPath);
			break;
		}

		m_pMaterial[i] = pSubset[i].MatD3D;
	}

	// Optimize
	if(m_pMesh->GetNumFaces() > 0)
	{
		DWORD* pAdjacency = new DWORD[m_pMesh->GetNumFaces() * 3];
		m_pMesh->GenerateAdjacency(0.0f, pAdjacency);
		m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, pAdjacency, NULL, NULL, NULL);
		delete[] pAdjacency;
	}

	// BufType
	m_eBufType = BUF_TYPE_STATIC_MESH;

	// FVF
	m_dwFVF = m_pMesh->GetFVF();

	// VtxCnt
	m_dwVtxCnt = m_pMesh->GetNumVertices();

	// VtxSize
	m_dwVtxSize = m_pMesh->GetNumBytesPerVertex();
}

CStaticMesh::~CStaticMesh()
{
	if(m_dwRefCnt != 0)
		return;

	if(m_pMaterial != NULL)
	{
		delete[] m_pMaterial;
		m_pMaterial = NULL;
	}

	if(m_ppDiffuseTexture != NULL)
	{
		for(DWORD i = 0; i < m_dwSubsetCnt; ++i)
		{
			if(m_ppDiffuseTexture[i] != NULL)
				m_ppDiffuseTexture[i]->Release();
		}

		delete[] m_ppDiffuseTexture;
	}

	if(m_ppNormalTexture != NULL)
	{
		for(DWORD i = 0; i < m_dwSubsetCnt; ++i)
		{
			if(m_ppNormalTexture[i] != NULL)
				m_ppNormalTexture[i]->Release();
		}

		delete[] m_ppNormalTexture;
	}

	if(m_ppSpecularTexture != NULL)
	{
		for(DWORD i = 0; i < m_dwSubsetCnt; ++i)
		{
			if(m_ppSpecularTexture[i] != NULL)
				m_ppSpecularTexture[i]->Release();
		}

		delete[] m_ppSpecularTexture;
	}

	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	if(m_pSubset!= NULL)
	{
		m_pSubset->Release();
		m_pSubset = NULL;
	}
}

int CStaticMesh::Update()
{
	return 0;
}

void CStaticMesh::Render()
{
}

CStaticMesh* CStaticMesh::Clone()
{
	CStaticMesh* pClone = new CStaticMesh;

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

	// Mesh
	pClone->m_pMesh = m_pMesh;

	// Subset
	pClone->m_pSubset = m_pSubset;

	// SubsetCnt
	pClone->m_dwSubsetCnt = m_dwSubsetCnt;

	// DiffuseTexture
	pClone->m_ppDiffuseTexture = m_ppDiffuseTexture;

	// NormalTexture
	pClone->m_ppNormalTexture = m_ppNormalTexture;

	// SpecularTexture
	pClone->m_ppSpecularTexture = m_ppSpecularTexture;

	// Material
	pClone->m_pMaterial = m_pMaterial;

	return pClone;
}