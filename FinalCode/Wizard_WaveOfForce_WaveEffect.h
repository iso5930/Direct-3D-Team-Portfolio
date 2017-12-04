#pragma once
#include "effect.h"

class CWizard_WaveOfForce_WaveEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void AddCCollision();

public:
	explicit CWizard_WaveOfForce_WaveEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_WaveOfForce_WaveEffect(void);
};