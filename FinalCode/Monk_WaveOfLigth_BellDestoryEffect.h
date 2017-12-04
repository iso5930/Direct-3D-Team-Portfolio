#pragma once
#include "effect.h"

class CMonk_WaveOfLigth_BellDestoryEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_WaveOfLigth_BellDestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_WaveOfLigth_BellDestoryEffect(void);
};