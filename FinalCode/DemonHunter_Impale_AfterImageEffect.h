#pragma once
#include "effect.h"

class CDemonHunter_Impale_AfterImageEffect : public CEffect
{
private:
	float		m_fTime;
	float		m_fAngle;
	D3DXVECTOR3 m_vAxis;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
 	explicit CDemonHunter_Impale_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vAxis, float _fAngle);
	virtual ~CDemonHunter_Impale_AfterImageEffect(void);
};