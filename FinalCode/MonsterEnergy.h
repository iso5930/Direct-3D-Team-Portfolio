#pragma once

#include "EnergyUI.h"

class CMonster;
class CBasicSign;

class CMonsterEnergy : public CEnergyUI
{
private:
	// Owner
	CMonster* m_pOwner;

	// HPBox
	CBasicSign* m_pHPBox;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonsterEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CMonster* _pOwner);
	virtual ~CMonsterEnergy();
};
