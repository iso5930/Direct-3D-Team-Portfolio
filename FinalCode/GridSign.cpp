#include "StdAfx.h"
#include "GridSign.h"

CGridSign::CGridSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CSignUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CGridSign::~CGridSign()
{
	Release();
}

void CGridSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CGridSign::Update()
{
	CSignUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	return 0;
}

void CGridSign::Render()
{
	CSignUI::Render();
}

void CGridSign::Release()
{
}