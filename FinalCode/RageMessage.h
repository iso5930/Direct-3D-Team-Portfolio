#pragma once

#include "MessageUI.h"

class CRageMessage : public CMessageUI
{
private:
	// Rage
	int m_iRage;

	// MaxLife
	int m_iMaxRage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CRageMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CRageMessage();
};
