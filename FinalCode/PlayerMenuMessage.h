#pragma once

#include "MessageUI.h"

class CPlayerMenuMessage : public CMessageUI
{
private:
	// Owner
	CPlayer* m_pOwner;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CPlayerMenuMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner);
	virtual ~CPlayerMenuMessage();
};
