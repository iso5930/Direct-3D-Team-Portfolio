#include "StdAfx.h"
#include "FollowerMenuMessage.h"

CFollowerMenuMessage::CFollowerMenuMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CFollower* _pOwner)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_FollowerMenu"))
{
	// Owner
	m_pOwner = _pOwner;

	// Text
	if(m_pOwner->GetFollowerInfo()->eFollowerType == FOLLOWER_TYPE_ENCHANTRESS)
		_tcscpy_s(m_tszText, MAX_STR, _T("¿ä¼ú»ç"));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.782993f, 0.641995f, 0.0f);
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.171009f, 0.155009f, 0.0f);
}

CFollowerMenuMessage::~CFollowerMenuMessage()
{
	Release();
}

void CFollowerMenuMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CFollowerMenuMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CFollowerMenuMessage::Render()
{
	CMessageUI::Render();

	RECT rcText;
	SetRect(&rcText, 39, 108, 239, 120);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CFollowerMenuMessage::Release()
{
}