#pragma once
#include "traileffect_2.h"

class CWizard_MagicMissile_TrailEffect : public CTrailEffect_2
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_MagicMissile_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CWizard_MagicMissile_TrailEffect(void);
};