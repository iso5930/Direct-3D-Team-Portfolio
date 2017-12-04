#pragma once

#include "Trigger.h"

class CMainQuest2_Trigger : public CTrigger
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// MonsterVec
	vector<CMonster*> m_MonsterVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

	// Mode2
	void Mode2();

	// Mode3
	void Mode3();

	// Mode4
	void Mode4();

	// Mode5
	void Mode5();

public:
	explicit CMainQuest2_Trigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMainQuest2_Trigger();
};
