#pragma once

#include "Player.h"

class CWizard_Male : public CPlayer
{
private:
	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Attack
	virtual int Attack();

	// LevelUp
	virtual void LevelUp();

	// Damage
	virtual void Damage(CMonster* _pMonster);

	// Damage
	virtual void Damage(CEffect* _pEffect);

	// Renew
	virtual void Renew();

	// CreateAttack
	virtual void CreateAttack();

	// SetSlot
	virtual void SetSlot(int _iIndex, CSlot* _pSlot);

	// TotalStat
	virtual int TotalStat1();
	virtual int TotalStat2();
	virtual int TotalStat3();

public:
	explicit CWizard_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWizard_Male();
};
