#pragma once
#include "effect.h"

class CMonk_MantraOfConviction_CastingEffect : public CEffect
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
	explicit CMonk_MantraOfConviction_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_MantraOfConviction_CastingEffect(void);
};