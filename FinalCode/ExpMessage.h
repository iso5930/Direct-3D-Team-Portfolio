#pragma once

#include "MessageUI.h"

class CExpMessage : public CMessageUI
{
private:
	// Exp
	int m_iExp;

	// MaxExp
	int m_iMaxExp;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CExpMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CExpMessage();
};
