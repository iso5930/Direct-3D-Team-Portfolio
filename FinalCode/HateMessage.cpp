#include "StdAfx.h"
#include "HateMessage.h"

CHateMessage::CHateMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("악마사냥꾼의 공격 기술에 사용됩니다.\n빠르게 회복됩니다."));

	// Hate
	m_iHate = 0;

	// MaxHate
	m_iMaxHate = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.448f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.412f, 0.202f, 0.0f);
}

CHateMessage::~CHateMessage()
{
	Release();
}

void CHateMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CHateMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iHate = ((CPlayer*)pPlayer)->GetStat()->iHate;
		m_iMaxHate = ((CPlayer*)pPlayer)->GetStat()->iMaxHate;
	}

	return 0;
}

void CHateMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("증오: "), m_iHate, m_iMaxHate);

	RECT rcText;
	SetRect(&rcText, 808, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 808, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CHateMessage::Release()
{
}