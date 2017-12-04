#pragma once
#include "monster.h"

class CSkeleton_OneHand_Blue :
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
	explicit CSkeleton_OneHand_Blue(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CSkeleton_OneHand_Blue(void);
};
