#pragma once

#include "Monster.h"

class CZombie_Skinny_Male_White : public CMonster
{
private:
	// LeftHandBone
	Bone m_LeftHandBone;

	// RightHandBone
	Bone m_RightHandBone;

	// HeadBone
	Bone m_HeadBone;

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
	explicit CZombie_Skinny_Male_White(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CZombie_Skinny_Male_White();
};
