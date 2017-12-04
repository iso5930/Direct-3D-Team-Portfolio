#pragma once

class CPlayer;
class CTransformCom;
class CPathFindCom;
class CAnimController;
class CObject;

class CPlayerState
{
protected:
	// StateType
	STATE_TYPE m_eStateType;

	// Owner
	CPlayer* m_pOwner;

	// TransformCom
	CTransformCom* m_pTransformCom;

	// PathFindCom
	CPathFindCom* m_pPathFindCom;

	// AnimController
	CAnimController* m_pAnimController;

public:
	virtual void Initialize() = 0;
	virtual CPlayerState* Action() = 0;

protected:
	int		UsingKeyMouse();

	bool	KeyMouseUP(int _KeyMouse);
	
	bool	KeyMousePress(int _KeyMouse);
	
	bool	KeyMouseDown(int _KeyMouse);

	void	KeyMouseStop(int _KeyMouse);

	int		OverObjectPick();

	void	PickObjectEvent();

	int		AttackMode();

public:
	// SetOwner
	void SetOwner(CPlayer* _pOwner) { m_pOwner = _pOwner; }

	// GetStateType
	STATE_TYPE GetStateType() { return m_eStateType; }

public:
	explicit CPlayerState();
	virtual ~CPlayerState();
};
