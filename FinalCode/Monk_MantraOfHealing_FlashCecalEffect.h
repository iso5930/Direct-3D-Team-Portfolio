#pragma once
#include "effect.h"

class CMonk_MantraOfHealing_FlashCecalEffect : public CEffect
{
private:
	int m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_MantraOfHealing_FlashCecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_MantraOfHealing_FlashCecalEffect(void);
};
