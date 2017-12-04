#pragma once
#include "effect.h"

class CNaviCell;
class CWizard_EnergyTwister_TwisterEffect;
class CCollisionCom;
class CWizard_EnergyTwister_TornadoEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	CNaviCell*	m_pCell;
	CWizard_EnergyTwister_TwisterEffect* m_pTwisterEffect;
	float		m_fDamegaTime;
	CCollisionCom* m_pCollisionCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_EnergyTwister_TornadoEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CWizard_EnergyTwister_TornadoEffect(void);
};