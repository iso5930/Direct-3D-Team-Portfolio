#include "StdAfx.h"
#include "BloodDecalEffect.h"

CBloodDecalEffect::CBloodDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CEffect(_tszObjKey, _eObjType, NULL)
{
	// Time
	m_fTime = 0.0f;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(pMaterialCom);

	int iRand = rand() % 8;
	if(iRand == 0)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_1"));
	else if(iRand == 1)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_2"));
	else if(iRand == 2)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_3"));
	else if(iRand == 3)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_4"));
	else if(iRand == 4)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_5"));
	else if(iRand == 5)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_6"));
	else if(iRand == 6)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_7"));
	else if(iRand == 7)
		pMaterialCom->m_pTexture = CTextureMgr::GetInstance()->GetTexture(_T("Effect_BloodDecal_8"));
}

CBloodDecalEffect::~CBloodDecalEffect()
{
	Release();
}

void CBloodDecalEffect::Initialize()
{
	CEffect::Initialize();

	// MapVec
	vector<CObject*> MapVec;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_MAP)->FindObjects(MapVec, _T("Map"));

	// Variable
	CTransformCom* pMapTransformCom;
	CBufferCom* pMapBufferCom;
	CStaticMesh* pMapStaticMesh;
	IntersectInfo intersectInfo;
	D3DXVECTOR3 vDown = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	for(size_t i = 0; i < MapVec.size(); ++i)
	{
		// MapTransformCom
		pMapTransformCom = (CTransformCom*)MapVec[i]->GetComponent(COM_TYPE_TRANSFORM);

		// MapBufferCom
		pMapBufferCom = (CBufferCom*)MapVec[i]->GetComponent(COM_TYPE_BUFFER);

		// MapStaticMesh
		pMapStaticMesh = (CStaticMesh*)pMapBufferCom->m_BufferVec[0];

		// Intersect
		D3DXIntersect(pMapStaticMesh->m_pMesh, &(m_pTransformCom->m_vPos - pMapTransformCom->m_vPos + D3DXVECTOR3(0.0f, 50.0f, 0.0f)), &vDown, &intersectInfo.bHit, &intersectInfo.dwFaceIndex, &intersectInfo.u, &intersectInfo.v, &intersectInfo.dist, &intersectInfo.pBuffer, &intersectInfo.dwCountOfHits);

		// Is Hit??
		if(intersectInfo.bHit)
			m_pTransformCom->m_vPos += vDown * (intersectInfo.dist - 50.0f);
	}

	// Angle
	m_pTransformCom->m_vAngle.y = D3DX_PI * 2.0f * (rand() % 1000) / 1000.0f;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(50.0f, 100.0f, 50.0f);
}

int CBloodDecalEffect::Update()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 5.0f)
		Destroy();

	CEffect::Update();

	return 0;
}

void CBloodDecalEffect::Render()
{
	CEffect::Render();
}

void CBloodDecalEffect::Release()
{
}