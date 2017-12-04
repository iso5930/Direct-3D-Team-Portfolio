#pragma once
#include "effect.h"

class CWizard_MagicMissile_CreateEffect : public CEffect
{
private:
	float m_fTime;
	float m_fCreateTime;
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_MagicMissile_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, float _fCreateTime);
	virtual ~CWizard_MagicMissile_CreateEffect(void);
};