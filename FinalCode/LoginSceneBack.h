#pragma once

#include "Back.h"

class CLoginSceneBack : public CBack
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CLoginSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CLoginSceneBack();
};