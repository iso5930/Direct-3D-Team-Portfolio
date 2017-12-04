#pragma once
#include "effect.h"

class CMonk_SevenSidedStrike_AfterImageEffect : public CEffect
{
private:
	float m_fTime;
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_SevenSidedStrike_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CMonk_SevenSidedStrike_AfterImageEffect(void);
};
