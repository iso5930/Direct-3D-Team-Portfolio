#include "StdAfx.h"
#include "ControlMessage.h"

CControlMessage::CControlMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("악마사냥꾼의 전술적 기술에 사용됩니다.\n천천히 회복됩니다."));

	// Control
	m_iControl = 0;

	// MaxControl
	m_iMaxControl = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.442f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.44f, 0.202f, 0.0f);
}

CControlMessage::~CControlMessage()
{
	Release();
}

void CControlMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CControlMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iControl = ((CPlayer*)pPlayer)->GetStat()->iControl;
		m_iMaxControl = ((CPlayer*)pPlayer)->GetStat()->iMaxControl;
	}

	return 0;
}

void CControlMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("절제: "), m_iControl, m_iMaxControl);

	RECT rcText;
	SetRect(&rcText, 796, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 796, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CControlMessage::Release()
{
}