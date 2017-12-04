#pragma once

class CNPC;
class CAnimController;

class CNPCState
{
protected:
	// StateType
	STATE_TYPE m_eStateType;

	// Owner
	CNPC* m_pOwner;

	// AnimController
	CAnimController* m_pAnimController;

public:
	virtual void Initialize() = 0;
	virtual CNPCState* Action() = 0;

public:
	// SetOwner
	void SetOwner(CNPC* _pOwner) { m_pOwner = _pOwner; }

	// GetStateType
	STATE_TYPE GetStateType() { return m_eStateType; }

public:
	explicit CNPCState();
	virtual ~CNPCState();
};
