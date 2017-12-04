#pragma once
#include "monster.h"

class CSkeleton_Summoner_Brown :
	public CMonster
{
public:
	// LeftHandBone
	Bone m_LeftHandBone;

	// RightHandBone
	Bone m_RightHandBone;

	// CenterBone
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
	explicit CSkeleton_Summoner_Brown(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CSkeleton_Summoner_Brown(void);
};
