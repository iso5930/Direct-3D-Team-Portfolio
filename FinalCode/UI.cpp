#include "StdAfx.h"
#include "UI.h"

CUI::CUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CObject(_tszObjKey, _eObjType)
{
	// State
	m_dwState = 0;

	// BackTexture
	m_pBackTexture = NULL;
	if(_tszBackTexKey != NULL)
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_tszBackTexKey);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_UI);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_UI);
	AddComponent(pRenderCom);

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);
}

CUI::~CUI()
{
	Release();
}

void CUI::Initialize()
{
	CObject::Initialize();

	// State
	m_dwState = 0;

	D3DXVECTOR3 vMousePos;
	ScreenToProj(&vMousePos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vMousePos.x, vMousePos.y),
		&D3DXVECTOR2(m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f, m_pTransformCom->m_vPos.y - m_pTransformCom->m_vSize.y / 2.0f),
		&D3DXVECTOR2(m_pTransformCom->m_vPos.x + m_pTransformCom->m_vSize.x / 2.0f, m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f)))
	{
		m_dwState |= UI_OVER;

		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			m_dwState |= UI_L_DOWN;

		if(CInputMgr::GetInstance()->MousePress(DIM_LBUTTON))
			m_dwState |= UI_L_PRESS;

		if(CInputMgr::GetInstance()->MouseUp(DIM_LBUTTON))
			m_dwState |= UI_L_UP;

		if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
			m_dwState |= UI_R_DOWN;

		if(CInputMgr::GetInstance()->MousePress(DIM_RBUTTON))
			m_dwState |= UI_R_PRESS;

		if(CInputMgr::GetInstance()->MouseUp(DIM_RBUTTON))
			m_dwState |= UI_R_UP;
	}

	// Texture
	m_pMaterialCom->m_pTexture = m_pBackTexture;
}

int CUI::Update()
{
	CObject::Update();

	m_dwState = 0;

	D3DXVECTOR3 vMousePos;
	ScreenToProj(&vMousePos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vMousePos.x, vMousePos.y),
				   &D3DXVECTOR2(m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f, m_pTransformCom->m_vPos.y - m_pTransformCom->m_vSize.y / 2.0f),
				   &D3DXVECTOR2(m_pTransformCom->m_vPos.x + m_pTransformCom->m_vSize.x / 2.0f, m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f)))
	{
		m_dwState |= UI_OVER;

		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			m_dwState |= UI_L_DOWN;

		if(CInputMgr::GetInstance()->MousePress(DIM_LBUTTON))
			m_dwState |= UI_L_PRESS;

		if(CInputMgr::GetInstance()->MouseUp(DIM_LBUTTON))
			m_dwState |= UI_L_UP;

		if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
			m_dwState |= UI_R_DOWN;

		if(CInputMgr::GetInstance()->MousePress(DIM_RBUTTON))
			m_dwState |= UI_R_PRESS;

		if(CInputMgr::GetInstance()->MouseUp(DIM_RBUTTON))
			m_dwState |= UI_R_UP;
	}

	return 0;
}

void CUI::Render()
{
	CObject::Render();
	m_pMaterialCom->m_pTexture = m_pBackTexture;
}

void CUI::Release()
{
}

void CUI::SetState(DWORD _dwState)
{
	m_dwState = _dwState; 
}

void CUI::AddState(DWORD _dwState)
{
	m_dwState |= _dwState; 
}

void CUI::RemoveState(DWORD _dwState)
{
	m_dwState &= ~(_dwState); 
}

bool CUI::IsOver()
{
	if(m_dwState & UI_OVER)
		return true;

	return false;
}

bool CUI::IsLDown()
{
	if(m_dwState & UI_L_DOWN)
		return true;

	return false;
}

bool CUI::IsLPress()
{
	if(m_dwState & UI_L_PRESS)
		return true;

	return false;
}

bool CUI::IsLUp()
{
	if(m_dwState & UI_L_UP)
		return true;

	return false;
}

bool CUI::IsRDown()
{
	if(m_dwState & UI_R_DOWN)
		return true;

	return false;
}

bool CUI::IsRPress()
{
	if(m_dwState & UI_R_PRESS)
		return true;

	return false;
}

bool CUI::IsRUp()
{
	if(m_dwState & UI_R_UP)
		return true;

	return false;
}