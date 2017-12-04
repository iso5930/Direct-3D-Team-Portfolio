#pragma once
#include "effect.h"

class CMonk_WayOfTheHundredFists_CreateEffect : public CEffect
{
private:
	float	m_fTime;
	float	m_fCreateTime;
	DWORD	m_dwNum;
	int		m_iMode;
	float	m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_WayOfTheHundredFists_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fTime, DWORD _dwNum);
	virtual ~CMonk_WayOfTheHundredFists_CreateEffect(void);
};