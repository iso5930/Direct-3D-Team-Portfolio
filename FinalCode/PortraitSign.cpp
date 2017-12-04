#include "StdAfx.h"
#include "PortraitSign.h"

CPortraitSign::CPortraitSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CSignUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CPortraitSign::~CPortraitSign()
{
	Release();
}

void CPortraitSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;
}

int CPortraitSign::Update()
{
	CSignUI::Update();

	return 0;
}

void CPortraitSign::Render()
{
	CSignUI::Render();
}

void CPortraitSign::Release()
{
}