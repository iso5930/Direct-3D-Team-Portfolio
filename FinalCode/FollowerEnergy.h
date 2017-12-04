#pragma once

#include "EnergyUI.h"

class CFollower;
class CBasicSign;
class CFollowerMenuMessage;

class CFollowerEnergy : public CEnergyUI
{
private:
	// Owner
	CFollower* m_pOwner;

	// HPBox
	CBasicSign* m_pHPBox;

	// Portrait
	CBasicSign* m_pPortrait;

	// MenuMessage
	CFollowerMenuMessage* m_pMenuMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Enable
	void Enable();

	// Disable
	void Disable();

public:
	explicit CFollowerEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CFollower* _pOwner);
	virtual ~CFollowerEnergy();
};
