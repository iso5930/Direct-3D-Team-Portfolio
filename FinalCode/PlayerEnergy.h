#pragma once

#include "EnergyUI.h"

class CPlayer;
class CBasicSign;
class CPlayerMenuMessage;

class CPlayerEnergy : public CEnergyUI
{
private:
	// Owner
	CPlayer* m_pOwner;

	// HPBox
	CBasicSign* m_pHPBox;

	// Portrait
	CBasicSign* m_pPortrait;

	// MenuMessage
	CPlayerMenuMessage* m_pMenuMessage;

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
	explicit CPlayerEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner);
	virtual ~CPlayerEnergy();
};
