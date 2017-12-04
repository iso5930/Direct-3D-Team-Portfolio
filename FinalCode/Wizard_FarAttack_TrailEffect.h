#pragma once
#include "traileffect.h"

class CWizard_FarAttack_TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_FarAttack_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CWizard_FarAttack_TrailEffect(void);
};
