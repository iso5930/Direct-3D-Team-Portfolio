#pragma once

#include "Follower.h"

class CEnchantress : public CFollower
{
private:
	// Time
	float m_fTime;

	// RightWeaponBone
	Bone m_RightWeaponBone;

	// LeftWeaponBone
	Bone m_LeftWeaponBone;

	// LeftShieldBone
	Bone m_LeftShieldBone;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

	// TotalStat
	virtual int TotalStat1();
	virtual int TotalStat2();
	virtual int TotalStat3();

public:
	explicit CEnchantress(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner, FollowerInfo* _pFollowerInfo);
	virtual ~CEnchantress();
};
