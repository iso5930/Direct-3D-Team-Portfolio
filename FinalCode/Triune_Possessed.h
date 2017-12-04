#pragma once
#include "monster.h"

class CTriune_Possessed :
	public CMonster
{
private:
	// LeftHandBone
	Bone m_LeftHandBone;

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
	explicit CTriune_Possessed(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CTriune_Possessed(void);
};
