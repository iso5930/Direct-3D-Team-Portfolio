#include "StdAfx.h"
#include "ManaMessage.h"

CManaMessage::CManaMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("부두술사는 마나를 사용하여 주문을 시전합니다.\n마나는 지속적으로 회복됩니다."));

	// Mana
	m_iMana = 0;

	// MaxMana
	m_iMaxMana = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.439f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.518f, 0.202f, 0.0f);
}

CManaMessage::~CManaMessage()
{
	Release();
}

void CManaMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CManaMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iMana = ((CPlayer*)pPlayer)->GetStat()->iMana;
		m_iMaxMana = ((CPlayer*)pPlayer)->GetStat()->iMaxMana;
	}

	return 0;
}

void CManaMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("마나: "), m_iMana, m_iMaxMana);

	RECT rcText;
	SetRect(&rcText, 771, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 771, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CManaMessage::Release()
{
}