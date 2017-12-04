#pragma once

#include "Slot.h"

class CDemonHunterHungeringArrowSlot : public CSlot
{
public:
	// Begin
	virtual SLOT_RESULT Begin(int _iMode);

	// Action
	virtual SLOT_RESULT Action();

	// End
	virtual SLOT_RESULT End();

private:
	// Mode0
	void Mode0(Bone& _WeaponBone);

	// Mode1
	void Mode1(Bone& _WeaponBone);

public:
	explicit CDemonHunterHungeringArrowSlot();
	virtual ~CDemonHunterHungeringArrowSlot();
};