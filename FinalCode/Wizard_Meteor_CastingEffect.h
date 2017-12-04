#pragma once
#include "effect.h"

class CWizard_Meteor_CastingEffect : public CEffect
{
private:
	float m_fRingCreateTime;
	float m_fMeteorCreateTime;

	CTransformCom	m_PlayerInfo;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Meteor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Meteor_CastingEffect(void);
};