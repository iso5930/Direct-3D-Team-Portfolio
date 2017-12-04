#include "StdAfx.h"
#include "VisionMessage.h"

CVisionMessage::CVisionMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("마법사의 공격 기술에 사용됩니다.\n빠르게 회복됩니다."));

	// Vision
	m_iVision = 0;

	// MaxVision
	m_iMaxVision = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.443f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.373f, 0.202f, 0.0f);
}

CVisionMessage::~CVisionMessage()
{
	Release();
}

void CVisionMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CVisionMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iVision = ((CPlayer*)pPlayer)->GetStat()->iVision;
		m_iMaxVision = ((CPlayer*)pPlayer)->GetStat()->iMaxVision;
	}

	return 0;
}

void CVisionMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("비전력: "), m_iVision, m_iMaxVision);

	RECT rcText;
	SetRect(&rcText, 818, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 818, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CVisionMessage::Release()
{
}