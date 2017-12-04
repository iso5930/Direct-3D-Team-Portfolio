#pragma once
#include "effect.h"

class CWizard_SpectralBlade_CreateEffect : public CEffect
{
private:
	float	m_fTime;
	float	m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_SpectralBlade_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_SpectralBlade_CreateEffect(void);
};