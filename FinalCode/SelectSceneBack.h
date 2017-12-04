#pragma once

#include "Back.h"

class CSelectSceneBack : public CBack
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSelectSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CSelectSceneBack();
};
