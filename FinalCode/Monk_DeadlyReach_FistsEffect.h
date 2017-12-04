#pragma once
#include "effect.h"

class CMonk_DeadlyReach_TrailEffect;
class CMonk_DeadlyReach_FistsEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	CMonk_DeadlyReach_TrailEffect* m_pTrailEffect;
	float		m_fCreateTime;
	int			m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_DeadlyReach_FistsEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, float _fTime = 0);
	virtual ~CMonk_DeadlyReach_FistsEffect(void);
};