#pragma once
#include "effect.h"

class CWizard_Meteor_MeteorEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vDestPos;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Meteor_MeteorEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, D3DXVECTOR3 _vDestPos);
	virtual ~CWizard_Meteor_MeteorEffect(void);
};
