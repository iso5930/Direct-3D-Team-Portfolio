#pragma once
#include "effect.h"

class CWizard_ArcaneOrb_GalaxyEffect : public CEffect
{
public:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_ArcaneOrb_GalaxyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_ArcaneOrb_GalaxyEffect(void);
};