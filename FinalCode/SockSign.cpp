#include "StdAfx.h"
#include "SockSign.h"

CSockSign::CSockSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CSignUI(_tszObjKey, _eObjType, NULL)
{
	// Item
	m_pItem = NULL;
	if(_pItem != NULL)
		m_pItem = new Item(_pItem);

	// BackTexture
	if(m_pItem != NULL)
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(m_pItem->tszTexKey);
	else
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Item_Sockets_1"));
}

CSockSign::~CSockSign()
{
	Release();
}

void CSockSign::Initialize()
{
	CSignUI::Initialize();
}

int CSockSign::Update()
{
	CSignUI::Update();

	return 0;
}

void CSockSign::Render()
{
	CSignUI::Render();
}

void CSockSign::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}
}