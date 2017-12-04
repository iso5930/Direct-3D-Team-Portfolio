#pragma once
#include "monster.h"

class CZombie_Male :
	public CMonster
{
private:
	// RightHandBone
	Bone m_RightHandBone;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void CreateAttack();
	virtual void Damage(CPlayer* _pPlayer);
	virtual void Damage(CEffect* _pEffect);

private:
	// DropZombieEyeBlue
	void DropZombieEyeBlue();

public:
	explicit CZombie_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CZombie_Male(void);
};
