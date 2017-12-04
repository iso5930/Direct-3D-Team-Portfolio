#pragma once
#include "effect.h"

class CMonk_SevenSidedStrike_DecalEffect : public CEffect
{
private:
	float m_fTime;
	float m_fCreateTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_SevenSidedStrike_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_SevenSidedStrike_DecalEffect(void);
};