#pragma once

#include "MessageUI.h"

class CDetailMessage : public CMessageUI
{
private:
	// Width
	int m_iWidth;

	// Height
	int m_iHeight;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDetailMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText);
	virtual ~CDetailMessage();
};
