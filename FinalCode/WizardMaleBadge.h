#pragma once

#include "BadgeUI.h"

class CWizardMaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizardMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWizardMaleBadge();
};
