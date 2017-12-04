#pragma once
#include "effect.h"

class CGhoul_Scratch_A :
	public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CGhoul_Scratch_A(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CGhoul_Scratch_A(void);
};
