#pragma once
#include "effect.h"

class CDemonHunter_Bola_FlashEffect : public CEffect
{
private:
	int		m_iMode;
	float	m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void	Mode1();
	void	Mode2();

public:
	explicit CDemonHunter_Bola_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Bola_FlashEffect(void);
};