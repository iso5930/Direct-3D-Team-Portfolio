#pragma once

#include "MessageUI.h"

class CDropMessage : public CMessageUI
{
private:
	// Width
	int m_iWidth;

	// Height
	int m_iHeight;

	// Color
	D3DXCOLOR m_dwColor;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDropMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CDropMessage();
};
