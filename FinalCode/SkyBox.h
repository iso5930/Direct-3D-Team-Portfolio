#pragma once

#include "Object.h"

class CSkyBox : public CObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkyBox(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszTexKey);
	virtual ~CSkyBox();
};
