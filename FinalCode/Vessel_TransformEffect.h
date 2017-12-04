#pragma once
#include "effect.h"

class CVessel_TransformEffect :
	public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CVessel_TransformEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, int _iTextureNumber);
	virtual ~CVessel_TransformEffect(void);
};
