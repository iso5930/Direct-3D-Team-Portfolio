#pragma once
#include "effect.h"

class CDemonHunter_Impale_KnivesTrailEffect;
class CDemonHunter_Impale_KnivesEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vAxis;
	float		m_fTime;
	float		m_fAngle;
	float		m_fAccTime;
	CDemonHunter_Impale_KnivesTrailEffect* m_pTrailEffect;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Impale_KnivesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CDemonHunter_Impale_KnivesEffect(void);
};