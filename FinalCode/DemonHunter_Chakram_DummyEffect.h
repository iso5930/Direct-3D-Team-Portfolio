#pragma once
#include "effect.h"

class CDemonHunter_Chakram_ChakramEffect;
class CDemonHunter_Chakram_DummyEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	CDemonHunter_Chakram_ChakramEffect* m_pChakramEffect;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Chakram_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_Chakram_DummyEffect(void);
};