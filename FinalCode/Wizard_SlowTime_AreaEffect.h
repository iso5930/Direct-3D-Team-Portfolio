#pragma once
#include "effect.h"

class CWizard_SlowTime_AreaEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_SlowTime_AreaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_SlowTime_AreaEffect(void);
};