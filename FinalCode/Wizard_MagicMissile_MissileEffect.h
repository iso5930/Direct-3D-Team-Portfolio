#pragma once
#include "effect.h"

class CWizard_MagicMissile_TrailEffect;
class CWizard_MagicMissile_MissileEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	float						m_fTime;
	CWizard_MagicMissile_TrailEffect* m_pTrailEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_MagicMissile_MissileEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CWizard_MagicMissile_MissileEffect(void);
};