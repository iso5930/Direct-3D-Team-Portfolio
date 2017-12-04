#include "StdAfx.h"
#include "ButtonUI.h"

CButtonUI::CButtonUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey, TCHAR* _tszDisableTexture)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Enable
	m_bEnable = true;

	// OverTexture
	m_pOverTexture = NULL;
	if(_tszOverTexKey != NULL)
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_tszOverTexKey);

	// DownTexture
	m_pDownTexture = NULL;
	if(_tszDownTexKey != NULL)
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_tszDownTexKey);

	// DisableTexture
	m_pDisableTexture = NULL;
	if(_tszDisableTexture != NULL)
		m_pDisableTexture = CTextureMgr::GetInstance()->GetTexture(_tszDisableTexture);
}

CButtonUI::~CButtonUI()
{
	Release();
}

void CButtonUI::Initialize()
{
	CUI::Initialize();

	if(m_bEnable == false)
		m_pMaterialCom->m_pTexture = m_pDisableTexture;
	else if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

int CButtonUI::Update()
{
	CUI::Update();

	if(m_dwState & UI_L_DOWN || m_dwState & UI_R_DOWN)
	{
		// PlaySoundForUI
		CSoundMgr::GetInstance()->PlaySoundForUI(_T("ClickButton.ogg"));
	}

	if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
	{
		CInputMgr::GetInstance()->MousePosInvalidate();
		CInputMgr::GetInstance()->MouseInvalidate(DIM_LBUTTON);

		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF0;

		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x0000000F;
	}

	if(m_dwState & UI_R_DOWN || m_dwState & UI_R_PRESS)
	{
		CInputMgr::GetInstance()->MousePosInvalidate();
		CInputMgr::GetInstance()->MouseInvalidate(DIM_RBUTTON);
		
		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF0;

		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x0000000F;
	}

	return 0;
}

void CButtonUI::Render()
{
	CUI::Render();

	if(m_bEnable == false)
		m_pMaterialCom->m_pTexture = m_pDisableTexture;
	else if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

void CButtonUI::Release()
{
}

void CButtonUI::Renew()
{
}

void CButtonUI::Enable()
{
	m_bEnable = true;

	if(m_bEnable == false)
		m_pMaterialCom->m_pTexture = m_pDisableTexture;
	else if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

void CButtonUI::Disable()
{
	m_bEnable = false;

	if(m_bEnable == false)
		m_pMaterialCom->m_pTexture = m_pDisableTexture;
	else if(m_dwState & UI_L_DOWN || m_dwState & UI_L_PRESS)
		m_pMaterialCom->m_pTexture = m_pDownTexture;
	else if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

bool CButtonUI::IsEnable()
{
	return m_bEnable;
}