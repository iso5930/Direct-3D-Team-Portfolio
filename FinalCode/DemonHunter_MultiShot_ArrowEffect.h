#pragma once
#include "effect.h"

class CDemonHunter_MultiShot_ArrowEffect : public CEffect
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
	explicit CDemonHunter_MultiShot_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_MultiShot_ArrowEffect(void);
};