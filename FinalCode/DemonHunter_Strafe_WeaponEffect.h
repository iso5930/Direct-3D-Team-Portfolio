#pragma once
#include "effect.h"

class CDemonHunter_Strafe_WeaponEffect : public CEffect
{
private:
	Bone  m_WeaponBone;
	D3DXMATRIX* m_pWorld;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Strafe_WeaponEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _pWeaponName, CHAR* _pBoneName);
	virtual ~CDemonHunter_Strafe_WeaponEffect(void);
};