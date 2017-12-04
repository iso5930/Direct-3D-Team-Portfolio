#pragma once
#include "effect.h"

class CWizard_Blizzard_CloudEffect : public CEffect
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
	explicit CWizard_Blizzard_CloudEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CWizard_Blizzard_CloudEffect(void);
};