#pragma once

#include "MessageUI.h"

class CLifeMessage : public CMessageUI
{
private:
	// Life
	int m_iLife;

	// MaxLife
	int m_iMaxLife;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CLifeMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CLifeMessage();
};
