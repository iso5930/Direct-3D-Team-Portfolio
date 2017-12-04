#pragma once

class CFollower;

class CFollowerState
{
protected:
	// Mode
	int m_iMode;

	// StateType
	STATE_TYPE m_eStateType;

	// Owner
	CFollower* m_pOwner;

	// PlayerTransformCom
	CTransformCom* m_pPlayerTransformCom;

	// TransformCom
	CTransformCom* m_pTransformCom;

	// PathFindCom
	CPathFindCom* m_pPathFindCom;

	// AnimController
	CAnimController* m_pAnimController;

public:
	virtual void Initialize() = 0;
	virtual CFollowerState* Action() = 0;

public:
	// SetOwner
	void SetOwner(CFollower* _pOwner) { m_pOwner = _pOwner; }

	// GetStateType
	STATE_TYPE GetStateType() { return m_eStateType; }

public:
	explicit CFollowerState(int _iMode);
	virtual ~CFollowerState();
};
