#pragma once
#include "effect.h"

class CZombie_Female_Scratch_A :
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
	explicit CZombie_Female_Scratch_A(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CZombie_Female_Scratch_A(void);
};
