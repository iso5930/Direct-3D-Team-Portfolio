#pragma once

class CMonster;
class CTransformCom;
class CPathFindCom;
class CAnimController;

class CMonsterState
{
protected:
	// StateType
	STATE_TYPE m_eStateType;

	// Owner
	CMonster* m_pOwner;

	// TransformCom
	CTransformCom* m_pTransformCom;

	// PathFindCom
	CPathFindCom* m_pPathFindCom;

	// AnimController
	CAnimController* m_pAnimController;

public:
	virtual void Initialize() = 0;
	virtual CMonsterState* Action() = 0;

public:
	// SetOwner
	void SetOwner(CMonster* _pOwner) { m_pOwner = _pOwner; }

	// GetStateType
	STATE_TYPE GetStateType() { return m_eStateType; }

public:
	explicit CMonsterState();
	virtual ~CMonsterState();
};
