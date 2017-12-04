#pragma once
#include "effect.h"

class CWarden_FireEffect :
	public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	D3DXVECTOR3					m_vDir;
	D3DXVECTOR3					m_vFirstPos;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWarden_FireEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 *_pDir);
	virtual ~CWarden_FireEffect(void);
};
