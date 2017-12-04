#pragma once
#include "monster.h"

class CSkeleton_Shield_Brown :
	public CMonster
{
public:
	// WeaponBone
	Bone m_WeaponBone;

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
	explicit CSkeleton_Shield_Brown(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CSkeleton_Shield_Brown(void);
};
