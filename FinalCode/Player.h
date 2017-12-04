#pragma once

#include "Object.h"

class CPlayerState;
class CDynamicMesh;
class CSlot;
class CCollisionCom;
class CBufferCom;
class CEquipItem;
class CMonster;
class CEffect;
class CFollower;
class CPlayerEnergy;

class CPlayer : public CObject
{
protected:
	// Time
	float m_fTime;

	// Info
	Info m_info;

	// Stat
	Stat m_stat;

	// State
	CPlayerState* m_pState;

	// DynamicMesh
	CDynamicMesh* m_pDynamicMesh[5];

	// Slot
	CSlot* m_pSlot[7];

	// BuffVec
	vector<Buff*> m_BuffVec;

	// MezVec
	vector<Mez*> m_MezVec;

	// CollisionCom
	CCollisionCom* m_pCollisionCom;

	// BufferCom
	CBufferCom* m_pBufferCom;

	// MainWeapon
	CEquipItem* m_pMainWeapon;

	// SubWeapon
	CEquipItem* m_pSubWeapon;

	// Helm
	CEquipItem* m_pHelm;
 
	// Shoulder
	CEquipItem* m_pShoulder;

	// PickObject
	CObject* m_pPickObject;

	// PickType
	int m_iPickType;

	// LastPushSlotNum
	int	m_iLastPushSlotNum;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetState
	CPlayerState* GetState() { return m_pState; }

	// GetInfo
	Info* GetInfo() { return &m_info; }

	// GetStat
	Stat* GetStat() { return &m_stat; }

	// GetSlot
	CSlot* GetSlot(int _iIndex) { return m_pSlot[_iIndex]; }

	// GetPickObject
	CObject* GetPickObject() { return m_pPickObject; }

	// SetPickObject
	void SetPickObject(CObject* _pPickObject) { m_pPickObject = _pPickObject; }

	// GetPickType
	int GetPickType() { return m_iPickType; }

	// SetPickType
	void SetPickType(int _iPickType) { m_iPickType = _iPickType; }

	// GetPickType
	int GetLastPushSlotNum() { return m_iLastPushSlotNum; }

	// SetPickType
	void SetLastPushSlotNum(int _iLastPushSlotNum) { m_iLastPushSlotNum = _iLastPushSlotNum; }

public:
	// Run
	void Run();

	// Stop
	void Stop();

	// Kill
	void Kill(int _iExp);

	// Attack
	virtual int Attack() = 0;

	// LevelUp
	virtual void LevelUp() = 0;

	// Damage
	virtual void Damage(CMonster* _pMonster) = 0;

	// Damage
	virtual void Damage(CEffect* _pEffect) = 0;

	// Renew
	virtual void Renew() = 0;

	// CreateAttack
	virtual void CreateAttack() = 0;

	// SetSlot
	virtual void SetSlot(int _iIndex, CSlot* _pSlot) = 0;

	// TotalStat
	virtual int TotalStat1() = 0;
	virtual int TotalStat2() = 0;
	virtual int TotalStat3() = 0;

public:
	// SetState
	void SetState(CPlayerState* _pState);

	// RemoveAttack
	void RemoveAttack();

	// AddBuff
	void AddBuff(Buff* _pBuff);

	// AddBuff
	void AddMez(Mez* _pMez);

	// AddBuff
	bool IsMez(int _iMez);

	// SetAnimation
	void SetAnimation(int _iIndex);

	// SetAnimationMode
	void SetAnimationMode(int _iMode);

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
	explicit CPlayer(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CPlayer();
};
