#pragma once

#include "BadgeUI.h"

class CWizardFemaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizardFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWizardFemaleBadge();
};
