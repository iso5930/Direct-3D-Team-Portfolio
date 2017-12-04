#pragma once
#include "effect.h"

class CWizard_Blizzard_IceCreateEffect : public CEffect
{
private:
	float	m_fTime;
	float	m_fAccTime;
	float	m_fCloudTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Blizzard_IceCreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Blizzard_IceCreateEffect(void);
};