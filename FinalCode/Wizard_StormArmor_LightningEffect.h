#pragma once
#include "effect.h"

class CWizard_StormArmor_LightningEffect : public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_StormArmor_LightningEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_StormArmor_LightningEffect(void);
};