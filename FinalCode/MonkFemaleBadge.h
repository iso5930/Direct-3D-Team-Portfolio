#pragma once

#include "BadgeUI.h"

class CMonkFemaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonkFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMonkFemaleBadge();
};
