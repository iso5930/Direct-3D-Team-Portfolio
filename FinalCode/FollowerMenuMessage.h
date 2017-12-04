#pragma once

#include "MessageUI.h"

class CFollowerMenuMessage : public CMessageUI
{
private:
	// Owner
	CFollower* m_pOwner;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CFollowerMenuMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CFollower* _pOwner);
	virtual ~CFollowerMenuMessage();
};
