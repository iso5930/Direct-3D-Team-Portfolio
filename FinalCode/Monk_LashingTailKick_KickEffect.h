#pragma once
#include "effect.h"

class CMonk_LashingTailKick_KickEffect : public CEffect
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
	explicit CMonk_LashingTailKick_KickEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CMonk_LashingTailKick_KickEffect(void);
};