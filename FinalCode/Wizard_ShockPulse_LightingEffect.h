#pragma once
#include "effect.h"

class CWizard_ShockPulse_LightingEffect : public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	float						m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_ShockPulse_LightingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_ShockPulse_LightingEffect(void);
};