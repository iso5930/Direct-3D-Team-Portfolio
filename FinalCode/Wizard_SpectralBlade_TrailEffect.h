#pragma once
#include "effect.h"

class CWizard_SpectralBlade_TrailEffect : public CEffect
{
private:
	int		m_iMode;
	float	m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_SpectralBlade_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_SpectralBlade_TrailEffect(void);
};