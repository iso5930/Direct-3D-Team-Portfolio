#pragma once

#include "Slot.h"

class CDemonHunterEvasiveFireSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();


private:
	// Mode0
	void Mode0(Bone& _WeaponBone);

	// Mode1
	void Mode1(Bone& _WeaponBone);

public:
	explicit CDemonHunterEvasiveFireSlot();
	virtual ~CDemonHunterEvasiveFireSlot();
};