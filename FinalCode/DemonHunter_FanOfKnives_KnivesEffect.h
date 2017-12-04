#pragma once
#include "effect.h"

class CDemonHunter_FanOfKnives_TrailEffect;
class CDemonHunter_FanOfKnives_KnivesEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	float		m_fAlpha;
	CDemonHunter_FanOfKnives_TrailEffect* m_pTrailEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
 	explicit CDemonHunter_FanOfKnives_KnivesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_FanOfKnives_KnivesEffect(void);
};