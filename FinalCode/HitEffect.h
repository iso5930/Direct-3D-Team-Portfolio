#pragma once
#include "effect.h"

class CHitEffect : public CEffect
{
private:
	float	m_fCreateTime;
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
	void Mode3();

public:
	explicit CHitEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fCreateTime);
	virtual ~CHitEffect(void);
};