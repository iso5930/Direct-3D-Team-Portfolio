#pragma once
#include "effect.h"

class CDemonHunter_RainOfVengeance_ArrowEffect : public CEffect
{
private:
	// Dir
	D3DXVECTOR3 m_vDir;

	//Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void AddCCollision();

public:
   explicit CDemonHunter_RainOfVengeance_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_RainOfVengeance_ArrowEffect(void);
};