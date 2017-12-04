#pragma once

#include "Monster.h"

class CZombie_Female : public CMonster
{
public:
	// LeftHandBone
	Bone m_LeftHandBone;

	// JawBone
	Bone m_JawBone;

	// PukeGroundBone
	Bone m_PukeGroundBone;

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
	// DropZombieEyeRed
	void DropZombieEyeRed();

public:
	explicit CZombie_Female(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CZombie_Female();
};
