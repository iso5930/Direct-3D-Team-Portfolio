#pragma once

#include "BadgeUI.h"

class CDemonHunterFemaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunterFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CDemonHunterFemaleBadge();
};
