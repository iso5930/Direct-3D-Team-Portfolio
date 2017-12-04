#pragma once
#include "effect.h"

class CWizard_ArcaneOrb_GalaxyEffect;
class CWizard_ArcaneOrb_OrbEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	CWizard_ArcaneOrb_GalaxyEffect* m_pGalaxyEffect[4];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void Destroy();

public:
	explicit CWizard_ArcaneOrb_OrbEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CWizard_ArcaneOrb_OrbEffect(void);
};