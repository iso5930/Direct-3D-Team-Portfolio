#pragma once
#include "effect.h"

class CCollisionCom;
class CWizard_Meteor_DecalEffect : public CEffect
{
private:
	float	m_fTime;
	float	m_fDemageTime;
	CCollisionCom* m_pCollisionCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Meteor_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Meteor_DecalEffect(void);
};