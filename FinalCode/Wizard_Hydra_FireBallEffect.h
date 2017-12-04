#pragma once
#include "effect.h"

class CWizard_Hydra_FireBallEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Hydra_FireBallEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CWizard_Hydra_FireBallEffect(void);
};
