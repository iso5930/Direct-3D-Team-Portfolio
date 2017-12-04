#pragma once

#include "Object.h"

class CPlayer;
class CFollowerState;
class CPathFindCom;
class CBufferCom;
class CDynamicMesh;
class CEquipItem;

class CFollower : public CObject
{
protected:
	// Owner
	CPlayer* m_pOwner;

	// FollowerInfo
	FollowerInfo m_FollowerInfo;

	// State
	CFollowerState* m_pState;

	// OwnerTransformCom
	CTransformCom* m_pOwnerTransformCom;

	// PathFindCom
	CPathFindCom* m_pPathFindCom;

	// BufferCom
	CBufferCom* m_pBufferCom;

	// DynamicMesh
	CDynamicMesh* m_pDynamicMesh;

	// MainWeapon
	CEquipItem* m_pMainWeapon;

	// SubWeapon
	CEquipItem* m_pSubWeapon;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew() = 0;

	// TotalStat
	virtual int TotalStat1() = 0;
	virtual int TotalStat2() = 0;
	virtual int TotalStat3() = 0;

public:
	// GetOwner
	CPlayer* GetOwner() { return m_pOwner; }

	// GetFollowerInfo
	FollowerInfo* GetFollowerInfo() { return &m_FollowerInfo; }

public:
	// SetState
	void SetState(CFollowerState* _pState);

	// SetAnimation
	void SetAnimation(int _iIndex);

public:
	// GetValue
	int GetAtt();
	int GetDef();

	// MainStat
	int GetStrength();
	int GetAgility();
	int GetIntelligence();
	int GetVitality();

	// AttackStat
	float GetReducedCooldownTime();
	float GetCriticalProbability();
	float GetCriticalDamage();

	// DefenseStat
	int GetPhysicalResistance();
	int GetColdResistance();
	int GetFlameResistance();
	int GetLightningResistance();
	int GetPoisonResistance();
	int GetHolyResistance();
	float GetReducedNearDamage();
	float GetReducedFarDamage();

	// LifeStat
	float GetRestoresBonus();
	int GetLifeRecoveryOfSecond();
	int GetLifeRecoveryOfHit();

	// ResourceStat
	int GetControlRecoveryOfSecond();
	int GetEffortRecoveryOfSecond();
	int GetHateRecoveryOfSecond();
	int GetManaRecoveryOfSecond();
	int GetRageRecoveryOfSecond();
	int GetVisionRecoveryOfSecond();
	float GetReducedControlConsumption();
	float GetReducedEffortConsumption();
	float GetReducedHateConsumption();
	float GetReducedManaConsumption();
	float GetReducedRageConsumption();
	float GetReducedVisionConsumption();

	// AdventureStat
	float GetExperience();
	float GetMagicItemsFound();
	float GetDiscoveryOfGoldCoins();

public:
	explicit CFollower(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner, FollowerInfo* _pFollowerInfo);
	virtual ~CFollower();
};
