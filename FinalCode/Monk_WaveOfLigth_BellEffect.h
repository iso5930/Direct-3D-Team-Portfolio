#pragma once
#include "effect.h"

class CMonk_WaveOfLigth_BellEffect : public CEffect
{
private:
	float	m_fTime;
	int		m_iMode;
	float	m_fLength;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_WaveOfLigth_BellEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_WaveOfLigth_BellEffect(void);
};