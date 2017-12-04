#include "StdAfx.h"
#include "FormulaButton.h"

CFormulaButton::CFormulaButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Formula* _pFormula)
: CButtonUI(_tszObjKey, _eObjType, _T("Button_Back_Formula"), _T("Button_Over_Formula"), _T("Button_Down_Formula"), NULL)
{
	// Formula
	m_pFormula = _pFormula;

	// Color
	m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if(m_pFormula->pItem->dwItemClass & ITEM_CLASS_NORMAL)
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(m_pFormula->pItem->dwItemClass & ITEM_CLASS_MAGIC)
		m_dwColor = D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f);
	else if(m_pFormula->pItem->dwItemClass & ITEM_CLASS_UNIQUE)
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	else if(m_pFormula->pItem->dwItemClass & ITEM_CLASS_LEGEND)
		m_dwColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(m_pFormula->pItem->dwItemClass & ITEM_CLASS_SET)
		m_dwColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
}

CFormulaButton::~CFormulaButton()
{
	Release();
}

void CFormulaButton::Initialize()
{
	CButtonUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CFormulaButton::Update()
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

void CFormulaButton::Render()
{
	CButtonUI::Render();

	if(Equals(m_pTransformCom->m_vSize.x, 0.0f, MIN_EPSILON) || Equals(m_pTransformCom->m_vSize.y, 0.0f, MIN_EPSILON))
		return;

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	TCHAR tszText[MIN_STR] = _T("- ");
	_tcscat_s(tszText, MIN_STR, m_pFormula->pItem->tszName);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 110.0f), long(vPos.y - 5.0f), long(vPos.x + 190.0f), long(vPos.y + 7.0f));

	if(m_dwState == 0)
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszText, -1, &rcText, DT_LEFT, m_dwColor);
	else
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CFormulaButton::Release()
{
}