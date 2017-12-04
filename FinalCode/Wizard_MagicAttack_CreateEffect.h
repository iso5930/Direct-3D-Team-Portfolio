#pragma once
#include "effect.h"

class CWizard_MagicAttack_CreateEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	float		m_fCreateTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_MagicAttack_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fTime);
	virtual ~CWizard_MagicAttack_CreateEffect(void);
};