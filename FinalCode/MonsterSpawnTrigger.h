#pragma once

#include "Trigger.h"

class CMonsterSpawnTrigger : public CTrigger
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// MonsterSpawnVec
	vector<MonsterSpawn*> m_MonsterSpawnVec;

	// MonsterVec
	vector<CMonster*> m_MonsterVec;

	// TimeVec
	vector<float> m_TimeVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// AddMonsterSpawn
	void AddMonsterSpawn(MonsterSpawn* _pMonsterSpawn);

private:
	// CreateMonster
	CMonster* CreateMonster(MonsterSpawn* _pMonsterSpawn);

public:
	explicit CMonsterSpawnTrigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMonsterSpawnTrigger();
};
