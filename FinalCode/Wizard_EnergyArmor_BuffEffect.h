#pragma once
#include "effect.h"

class CWizard_EnergyArmor_BuffEffect : public CEffect
{
private:
	float	m_fTime;
	D3DXVECTOR3* m_pPos;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_EnergyArmor_BuffEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CWizard_EnergyArmor_BuffEffect(void);
};