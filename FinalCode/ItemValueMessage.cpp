#include "StdAfx.h"
#include "ItemValueMessage.h"

CItemValueMessage::CItemValueMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_ItemValue"))
{
	// Item
	m_pItem = new Item(_pItem);
}

CItemValueMessage::~CItemValueMessage()
{
	Release();
}

void CItemValueMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CItemValueMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;

	return 0;
}

void CItemValueMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	// 판매가
	RECT rcText;
	SetRect(&rcText, long(vPos.x - 120), long(vPos.y - 6), long(vPos.x + 120), long(vPos.y + 8));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, _T("판매가: "), -1, &rcText, DT_LEFT, D3DXCOLOR(0.749019f, 0.698039f, 0.564705f, 1.0f));

	// 가격
	TCHAR tszValue[MIN_STR];
	_itot_s(m_pItem->iValue * m_pItem->iNum / 10, tszValue, 10);
	SetRect(&rcText, long(vPos.x - 70), long(vPos.y - 6), long(vPos.x + 120), long(vPos.y + 8));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, tszValue, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CItemValueMessage::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}
}