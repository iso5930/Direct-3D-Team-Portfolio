#pragma once
#include "effect.h"

class CWizard_ShockPulse_DummyEffect : public CEffect
{
private:
	float		m_fTime;
	D3DXVECTOR3 m_vDestPos;
	int			m_iMode;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vPoint;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_ShockPulse_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos);
	virtual ~CWizard_ShockPulse_DummyEffect(void);
};