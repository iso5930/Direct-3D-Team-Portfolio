#pragma once
#include "effect.h"

class CDemonHunter_Strafe_ArrowEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Strafe_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_Strafe_ArrowEffect(void);
};