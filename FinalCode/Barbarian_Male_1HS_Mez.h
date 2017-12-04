#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_Mez :	public CPlayerState
{
private:
	// Time
	float m_fTime; 

	// Time
	float m_fAccTime; 

	// Mez
	int	m_iMez;

	// OldColor
	D3DXVECTOR4 m_vOldColor;

	// OldColor
	D3DXVECTOR3 m_vPos;

private:
	// ENTANGLE
	CPlayerState* Mode0();

	// FULL
	CPlayerState* Mode1();

	// PUSH
	CPlayerState* Mode2();
	
	// STUN 
	CPlayerState* Mode3();
private:
	// SlotAction;
	CPlayerState* SlotAction(int _iIndex);

	// IsSlotRange
	bool IsSlotRange(int _iIndex);
		
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HS_Mez(int _iMez , D3DXVECTOR3& _vPos);
	virtual ~CBarbarian_Male_1HS_Mez(void);
};