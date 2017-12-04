#pragma once
#include "effect.h"

class CDemonHunter_ElementalArrow_FlashEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;
	int			m_iMode;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CDemonHunter_ElementalArrow_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CDemonHunter_ElementalArrow_FlashEffect(void);
};
