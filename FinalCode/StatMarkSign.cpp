#include "StdAfx.h"
#include "StatMarkSign.h"

CStatMarkSign::CStatMarkSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CSignUI(_tszObjKey, _eObjType, _T("Sign_StatMark"))
{
	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.012f, 0.021f, 0.0f);
}

CStatMarkSign::~CStatMarkSign()
{
	Release();
}

void CStatMarkSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;
}

int CStatMarkSign::Update()
{
	CSignUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;

	return 0;
}

void CStatMarkSign::Render()
{
	CSignUI::Render();
}

void CStatMarkSign::Release()
{
}