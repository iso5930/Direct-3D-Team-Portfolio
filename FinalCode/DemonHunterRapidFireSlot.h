#pragma once

#include "Slot.h"

class CDemonHunterRapidFireSlot : public CSlot
{
private:
	float		m_fTickTime;
	float		m_fCreateTime;

	D3DXVECTOR3	m_vPos;
private:
	void	Mode0();
	void	Mode1();
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CDemonHunterRapidFireSlot();
	virtual ~CDemonHunterRapidFireSlot();
};