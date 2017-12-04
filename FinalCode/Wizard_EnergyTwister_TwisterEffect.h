#pragma once
#include "effect.h"

class CWizard_EnergyTwister_TwisterEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_EnergyTwister_TwisterEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CWizard_EnergyTwister_TwisterEffect(void);
};