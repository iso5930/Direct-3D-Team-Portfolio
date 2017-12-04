#pragma once
#include "monster.h"

class CButcher :
	public CMonster
{
public:
	// RightWeaponBone
	Bone m_RightWeaponBone;

	// LeftWeaponBone
	Bone m_LeftWeaponBone;

	// Bone
	Bone m_CenterBone;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void CreateAttack();
	virtual void Damage(CPlayer* _pPlayer);
	virtual void Damage(CEffect* _pEffect);

public:
	explicit CButcher(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CButcher(void);
};
