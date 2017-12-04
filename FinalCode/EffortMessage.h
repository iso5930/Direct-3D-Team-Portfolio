#pragma once

#include "MessageUI.h"

class CEffortMessage : public CMessageUI
{
private:
	// Effort
	int m_iEffort;

	// MaxEffort
	int m_iMaxEffort;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CEffortMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CEffortMessage();
};
