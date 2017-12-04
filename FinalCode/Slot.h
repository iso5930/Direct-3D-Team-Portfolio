#pragma once

class CPlayer;
class CTransformCom;

class CSlot
{
protected:
	// Mode
	int m_iMode;

	// Owner
	CPlayer* m_pOwner;

	// TransformCom
	CTransformCom* m_pTransformCom;

	// SlotType
	SLOT_TYPE m_eSlotType;

	// SlotID
	SLOT_ID m_eSlotID;

	// Enable
	bool m_bEnable;

	// Time
	float m_fTime;

	// CooldownTime
	float m_fCooldownTime;

	// ChargingTime
	float m_fChargingTime;

	// ChargeTime
	float m_fChargeTime;

	// Charge
	int m_iCharge;

	// MaxCharge
	int m_iMaxCharge;

	// Range
	float m_fRange;
public:
	virtual SLOT_RESULT Begin(int _iMode) = 0;

	virtual SLOT_RESULT Action() = 0;

	virtual SLOT_RESULT End() = 0;

	virtual SLOT_RESULT Condition();

public:
	// GetTime
	float GetTime() { return m_fTime; }

	// GetChargingTime
	float GetChargingTime() { return m_fChargingTime; }

	// GetChargeTime
	float GetChargeTime() { return m_fChargeTime; }

	// GetCharge
	int GetCharge() { return m_iCharge; }

	// GetMaxCharge
	int GetMaxCharge() { return m_iMaxCharge; }

public:
	// GetCooldownTime
	float GetCooldownTime();

	// GetRange
	float GetRange(); 

	int Update();
	
	int	Charge();
	
public:
	// SetOwner
	void SetOwner(CPlayer* _pOwner);

	// GetSlotType
	SLOT_TYPE GetSlotType() { return m_eSlotType; }

	// GetSlotID
	SLOT_ID GetSlotID() { return m_eSlotID; }
	
public:
	explicit CSlot();
	virtual ~CSlot();
};
