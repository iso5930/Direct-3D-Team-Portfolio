#pragma once
#include "monster.h"

class CSkeleton_King :
	public CMonster
{
public:
	// WeaponBone
	Bone m_WeaponBone;

	// LeftHandBone
	Bone m_LeftHandBone;

	// CenterBone
	Bone m_CenterBone;

	// CenterTopBone
	Bone m_CenterTopBone;

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
	explicit CSkeleton_King(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CSkeleton_King(void);
};
