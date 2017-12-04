#pragma once

#include "BadgeUI.h"

class CBarbarianMaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CBarbarianMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CBarbarianMaleBadge();
};
