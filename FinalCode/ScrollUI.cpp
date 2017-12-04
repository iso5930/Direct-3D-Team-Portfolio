#include "StdAfx.h"
#include "ScrollUI.h"

CScrollUI::CScrollUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// OverTexture
	m_pOverTexture = NULL;
	if(_tszOverTexKey != NULL)
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_tszOverTexKey);

	// DownTexture
	m_pDownTexture = NULL;
	if(_tszDownTexKey != NULL)
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_tszDownTexKey);

	// Clicked
	m_bClicked = false;

	// Max
	m_fMax = 0.0f;

	// Min
	m_fMin = 0.0f;

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;
}

CScrollUI::~CScrollUI()
{
	Release();
}

void CScrollUI::Initialize()
{
	CUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF5;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x0000000A;

	if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

int CScrollUI::Update()
{
	CUI::Update();

	if(m_bClicked)
		Clicked();
	else
		NoneClicked();

	return 0;
}

void CScrollUI::Render()
{
	CUI::Render();

	if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

void CScrollUI::Release()
{
}

void CScrollUI::Setup(int _iScroll, int _iMaxScroll, float _fMax, float _fMin)
{
	m_iScroll = _iScroll;
	m_iMaxScroll = _iMaxScroll;
	m_fMax = _fMax;
	m_fMin = _fMin;
}

void CScrollUI::Clicked()
{
	if(CInputMgr::GetInstance()->MouseUp(DIM_LBUTTON))
		m_bClicked = false;

	m_dwState = m_dwState | UI_L_DOWN | UI_L_PRESS;
	CInputMgr::GetInstance()->MousePosInvalidate();
	CInputMgr::GetInstance()->MouseInvalidate();
}

void CScrollUI::NoneClicked()
{
	if(m_dwState & UI_L_DOWN)
		m_bClicked = true;
}