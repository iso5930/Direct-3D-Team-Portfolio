#pragma once

#include "Back.h"

class CCreateSceneBack : public CBack
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CCreateSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCreateSceneBack();
};
