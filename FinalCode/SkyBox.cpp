#include "StdAfx.h"
#include "SkyBox.h"

CSkyBox::CSkyBox(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszTexKey)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_SKYBOX);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_SKYBOX);
	AddComponent(pRenderCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _tszTexKey);
	AddComponent(pMaterialCom);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
}

CSkyBox::~CSkyBox()
{
	Release();
}

void CSkyBox::Initialize()
{
	CObject::Initialize();
}

int CSkyBox::Update()
{
	// Pos
	memcpy_s(&m_pTransformCom->m_vPos, sizeof(D3DXVECTOR3), CCameraMgr::GetInstance()->GetPos3D(), sizeof(D3DXVECTOR3));

	CObject::Update();

	return 0;
}

void CSkyBox::Render()
{
	CObject::Render();
}

void CSkyBox::Release()
{
}