#pragma once
#include "effect.h"

class CWaterEffect : public CEffect
{
public:
	float	m_fSpeedX;
	float	m_fSpeedY;
	bool	m_bCheck;
	float	m_fDetail;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWaterEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, float _fSpeedX, float _fSpeedY, TCHAR* _tszName, float _fDetail);
	virtual ~CWaterEffect(void);
};