#include "StdAfx.h"
#include "CategoryButton.h"

CCategoryButton::CCategoryButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszCategory)
: CButtonUI(_tszObjKey, _eObjType, NULL, NULL, NULL, NULL)
{
	// Open
	m_bOpen = false;

	// CloseTexture
	m_pCloseTexture[0] = m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Button_Back_CloseCategory"));
	m_pCloseTexture[1] = m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Button_Over_CloseCategory"));
	m_pCloseTexture[2] = m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Button_Down_CloseCategory"));

	// OpenTexture
	m_pOpenTexture[0] = CTextureMgr::GetInstance()->GetTexture(_T("Button_Back_OpenCategory"));
	m_pOpenTexture[1] = CTextureMgr::GetInstance()->GetTexture(_T("Button_Over_OpenCategory"));
	m_pOpenTexture[2] = CTextureMgr::GetInstance()->GetTexture(_T("Button_Down_OpenCategory"));

	// Category
	_tcscpy_s(m_tszCategory, MIN_STR, _tszCategory);
}

CCategoryButton::~CCategoryButton()
{
	Release();
}

void CCategoryButton::Initialize()
{
	CButtonUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CCategoryButton::Update()
{
	CButtonUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	return 0;
}

void CCategoryButton::Render()
{
	CButtonUI::Render();

	if(Equals(m_pTransformCom->m_vSize.x, 0.0f, MIN_EPSILON) || Equals(m_pTransformCom->m_vSize.y, 0.0f, MIN_EPSILON))
		return;

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x + 10.0f), long(vPos.y - 5.0f), long(vPos.x + 310.0f), long(vPos.y + 7.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszCategory, -1, &rcText, DT_LEFT, D3DXCOLOR(0.721568f, 0.615686f, 0.462745f, 1.0f));
}

void CCategoryButton::Release()
{
}

void CCategoryButton::Open()
{
	m_bOpen = true;
	m_pBackTexture = m_pOpenTexture[0];
	m_pOverTexture = m_pOpenTexture[1];
	m_pDownTexture = m_pOpenTexture[2];
}

void CCategoryButton::Close()
{
	m_bOpen = false;
	m_pBackTexture = m_pCloseTexture[0];
	m_pOverTexture = m_pCloseTexture[1];
	m_pDownTexture = m_pCloseTexture[2];
}