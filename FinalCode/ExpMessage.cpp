#include "StdAfx.h"
#include "ExpMessage.h"

CExpMessage::CExpMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Exp
	m_iExp = 0;

	// MaxExp
	m_iMaxExp = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.734f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CExpMessage::~CExpMessage()
{
	Release();
}

void CExpMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CExpMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iExp = ((CPlayer*)pPlayer)->GetStat()->iExp;
		m_iMaxExp = ((CPlayer*)pPlayer)->GetStat()->iMaxExp;
	}

	return 0;
}

void CExpMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("°æÇèÄ¡: "), m_iExp, m_iMaxExp);

	RECT rcText;
	SetRect(&rcText, 0, 615, WINCX, 632);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_CENTER, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_CALCRECT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));
	m_pTransformCom->m_vSize.x = (rcText.right - rcText.left) / float(WINCX) * 2.0f + 0.04f;
	m_pTransformCom->m_vSize.y = (rcText.bottom - rcText.top) / float(WINCY) * 2.0f + 0.04f;
}

void CExpMessage::Release()
{
}