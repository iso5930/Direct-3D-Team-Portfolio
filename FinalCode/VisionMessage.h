#pragma once

#include "MessageUI.h"

class CVisionMessage : public CMessageUI
{
private:
	// Vision
	int m_iVision;

	// MaxVision
	int m_iMaxVision;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CVisionMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CVisionMessage();
};
