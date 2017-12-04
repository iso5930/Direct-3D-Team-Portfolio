#pragma once
#include "effect.h"

class CDemonHunter_RainOfVengeance_StartEffect : public CEffect
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;
	float m_fAccTime;

	// DecalPos
	D3DXVECTOR3 m_vDecalPos;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

public:
	explicit CDemonHunter_RainOfVengeance_StartEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDecalPos);
	virtual ~CDemonHunter_RainOfVengeance_StartEffect(void);
};