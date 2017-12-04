#include "StdAfx.h"
#include "StoreGridSign.h"

CStoreGridSign::CStoreGridSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CSignUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0470093f, 0.20301f, 0.0f);
}

CStoreGridSign::~CStoreGridSign()
{
}

void CStoreGridSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;
}

int CStoreGridSign::Update()
{
	CSignUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;

	return 0;
}

void CStoreGridSign::Render()
{
	CSignUI::Render();
}

void CStoreGridSign::Release()
{
}