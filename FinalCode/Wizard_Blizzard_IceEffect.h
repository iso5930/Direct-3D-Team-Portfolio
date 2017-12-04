#pragma once
#include "effect.h"

class CWizard_Blizzard_IceEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	float		m_fDestY;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Blizzard_IceEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fDestY);
	virtual ~CWizard_Blizzard_IceEffect(void);
};