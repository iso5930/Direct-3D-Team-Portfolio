#pragma once
#include "effect.h"

class CMaterialCom;
class CWitchDoctor_FireBatsEffect : public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	D3DXVECTOR3					m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDoctor_FireBatsEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3& _vDir);
	virtual ~CWitchDoctor_FireBatsEffect(void);
};