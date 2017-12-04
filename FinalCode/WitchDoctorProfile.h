#pragma once

#include "ProfileUI.h"

class CWitchDoctorProfile : public CProfileUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDoctorProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWitchDoctorProfile();
};
