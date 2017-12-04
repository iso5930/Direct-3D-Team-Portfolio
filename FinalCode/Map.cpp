#include "StdAfx.h"
#include "Map.h"

CMap::CMap(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBufKey, TCHAR* _tszPath, TCHAR* _tszFile)
: CObject(_tszObjKey, _eObjType)
{
	// AddBuffer
	CBufferMgr::GetInstance()->AddBuffer(_tszBufKey, new CStaticMesh(_tszPath, _tszFile));

	// BufKey
	_tcscpy_s(m_tszBufKey, MIN_STR, _tszBufKey);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_MAP);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_MAP);
	AddComponent(pRenderCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(m_tszBufKey);
	AddComponent(pBufferCom);
}

CMap::~CMap()
{
	Release();
}

void CMap::Initialize()
{
	CObject::Initialize();
}

int CMap::Update()
{
	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 3060.0f) == false)
		return 0;

	CObject::Update();

	return 0;
}

void CMap::Render()
{
	CObject::Render();
}

void CMap::Release()
{
	// RemoveBuffer
	CSeamlessMgr::GetInstance()->RemoveMapBuffer(m_tszBufKey);
}