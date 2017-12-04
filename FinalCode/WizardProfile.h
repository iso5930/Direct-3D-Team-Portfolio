#pragma once

#include "ProfileUI.h"

class CWizardProfile : public CProfileUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizardProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWizardProfile();
};
