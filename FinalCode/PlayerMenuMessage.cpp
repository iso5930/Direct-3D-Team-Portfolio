#include "StdAfx.h"
#include "PlayerMenuMessage.h"

CPlayerMenuMessage::CPlayerMenuMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_PlayerMenu"))
{
	// Owner
	m_pOwner = _pOwner;

	// Text
	_tcscpy_s(m_tszText, MIN_STR, m_pOwner->GetInfo()->tszName);

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.902993f, 0.641995f, 0.0f);
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.171009f, 0.155009f, 0.0f);
}

CPlayerMenuMessage::~CPlayerMenuMessage()
{
	Release();
}

void CPlayerMenuMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CPlayerMenuMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CPlayerMenuMessage::Render()
{
	CMessageUI::Render();

	RECT rcText;
	SetRect(&rcText, -38, 108, 162, 120);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CPlayerMenuMessage::Release()
{
}