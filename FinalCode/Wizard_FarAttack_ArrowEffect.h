#pragma once
#include "effect.h"

class CWizard_FarAttack_TrailEffect;
class CWizard_FarAttack_ArrowEffect : public CEffect
{
private:
	// Dir
	D3DXVECTOR3 m_vDir;

	// TrailEffect
	CWizard_FarAttack_TrailEffect* m_pTrailEffect;
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_FarAttack_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CWizard_FarAttack_ArrowEffect(void);
};