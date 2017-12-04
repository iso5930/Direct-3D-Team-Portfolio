#pragma once
#include "monster.h"

class CWarden :
	public CMonster
{
private:
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
	explicit CWarden(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CWarden(void);
};