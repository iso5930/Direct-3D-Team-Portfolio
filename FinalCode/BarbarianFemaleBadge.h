#pragma once

#include "BadgeUI.h"

class CBarbarianFemaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CBarbarianFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CBarbarianFemaleBadge();
};
