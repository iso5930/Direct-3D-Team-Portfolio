#pragma once
#include "effect.h"

class CWizard_WaveOfForce_CreateEffect : public CEffect
{
private:
	float m_fTime;
	float m_fCreateTime;
	int m_iMode;
	int m_iCreateCount;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_WaveOfForce_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_WaveOfForce_CreateEffect(void);
};