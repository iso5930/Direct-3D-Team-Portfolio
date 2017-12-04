#pragma once
#include "effect.h"

class CMonk_FistsOfThunder_CreateEffect : public CEffect
{
private:
	float m_fCreateTime;
	float m_fTime;
	int		m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_FistsOfThunder_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fCreateTime, int _iMode);
	virtual ~CMonk_FistsOfThunder_CreateEffect(void);
};