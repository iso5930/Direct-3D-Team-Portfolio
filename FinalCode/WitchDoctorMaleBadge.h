#pragma once

#include "BadgeUI.h"

class CWitchDoctorMaleBadge : public CBadgeUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDoctorMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWitchDoctorMaleBadge();
};
