#pragma once
#include "effect.h"

class CDemonHunter_Chakram_ChakramEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Chakram_ChakramEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CDemonHunter_Chakram_ChakramEffect(void);
};