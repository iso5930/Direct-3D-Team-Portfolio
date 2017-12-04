#pragma once

#include "BadgeUI.h"

class CDemonHunterMaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunterMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CDemonHunterMaleBadge();
};
