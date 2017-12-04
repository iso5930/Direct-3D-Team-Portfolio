#pragma once
#include "effect.h"

class CWizard_MagicAttack_MissileEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	int			m_iMode;
	float		m_fModeTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

	virtual void Destroy();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_MagicAttack_MissileEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CWizard_MagicAttack_MissileEffect(void);
};