#pragma once

#include "BadgeUI.h"

class CMonkMaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonkMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMonkMaleBadge();
};
