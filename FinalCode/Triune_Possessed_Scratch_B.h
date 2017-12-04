#pragma once
#include "effect.h"

class CTriune_Possessed_Scratch_B :
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
	explicit CTriune_Possessed_Scratch_B(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CTriune_Possessed_Scratch_B(void);
};
