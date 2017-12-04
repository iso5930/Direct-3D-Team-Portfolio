#pragma once
#include "effect.h"

class CCollisionCom;
class CWizard_RayOfFrost_DummyEffect : public CEffect
{
private:
	float m_fTime;
	CCollisionCom* m_pCollisionCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_RayOfFrost_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_RayOfFrost_DummyEffect(void);
};