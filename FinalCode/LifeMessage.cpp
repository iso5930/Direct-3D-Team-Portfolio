#include "StdAfx.h"
#include "LifeMessage.h"

CLifeMessage::CLifeMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("생명력이 모두 떨어지면 죽습니다."));

	// Life
	m_iLife = 0;

	// MaxLife
	m_iMaxLife = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.433f, -0.611f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.365f, 0.15f, 0.0f);
}

CLifeMessage::~CLifeMessage()
{
	Release();
}

void CLifeMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CLifeMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
	if(pFindObject != NULL)
	{
		CPlayer* pPlayer = (CPlayer*)pFindObject;
		m_iLife = pPlayer->GetStat()->iLife;
		m_iMaxLife = int((pPlayer->GetStat()->iMaxLife + pPlayer->GetVitality() * 10) * pPlayer->GetRestoresBonus());
	}

	return 0;
}

void CLifeMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("생명력: "), m_iLife, m_iMaxLife);

	RECT rcText;
	SetRect(&rcText, 256, 562, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 256, 582, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CLifeMessage::Release()
{
}