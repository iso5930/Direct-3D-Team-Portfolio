#pragma once

#include "BadgeUI.h"

class CWitchDoctorFemaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDoctorFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWitchDoctorFemaleBadge();
};
