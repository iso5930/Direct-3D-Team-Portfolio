#pragma once
#include "effect.h"

class CDemonHunter_SpikeTrap_DecalGlowEffect;
class CDemonHunter_SpikeTrap_DecalEffect;
class CDemonHunter_SpikeTrap_SpikeEffect;
class CDemonHunter_SpikeTrap_FireEffect;
class CDemonHunter_SpikeTrap_TrapEffect : public CEffect
{
private:
	CDemonHunter_SpikeTrap_DecalEffect* m_pDecalEffect;
	CDemonHunter_SpikeTrap_DecalGlowEffect* m_pDecalGlowEffect;
	CDemonHunter_SpikeTrap_SpikeEffect* m_pSpikeEffect;
	CDemonHunter_SpikeTrap_FireEffect* m_pFireEffect;

private:
	int		m_iPrevHate;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_SpikeTrap_TrapEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_SpikeTrap_TrapEffect(void);
};