#pragma once
#include "effect.h"

class CZombie_Male_Scratch :
	public CEffect
{
private:
	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CZombie_Male_Scratch(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CZombie_Male_Scratch(void);
};
