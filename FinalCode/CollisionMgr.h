#pragma once

class CObject;

class CCollisionMgr
{
private:
	// Object Vector
	vector<CObject*> m_ObjectVec[COLL_TYPE_END];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// AddObject
	void AddObject(COLL_TYPE _eCollType, CObject* _pObject);

	// RemoveObject
	void RemoveObject(COLL_TYPE _eCollType, CObject* _pObject);

private:
	// PlayerToMonster
	void PlayerToMonster(CObject* _pPlayer, CObject* _pMonster);

	// MonsterToMonster
	void MonsterToMonster(CObject* _pMonsterA, CObject* _pMonsterB);

	// PlayerToEffect
	void PlayerToEffect(CObject* _pPlayer, CObject* _pEffect);

	// MonsterToEffect
	void MonsterToEffect(CObject* _pMonster, CObject* _pEffect);

	// PlayerToNPC
	void PlayerToNPC(CObject* _pPlayer, CObject* _pNPC);

	// PlayerToProb
	void PlayerToProb(CObject* _pPlayer, CObject* _pProb);

private:
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit CCollisionMgr();
	~CCollisionMgr();
};