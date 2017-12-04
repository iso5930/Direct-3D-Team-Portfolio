#pragma once
#include "effect.h"

class CDemonHunter_Bola_AfterImageEffect : public CEffect
{
private:
	float m_fTime;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Bola_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Bola_AfterImageEffect(void);
};