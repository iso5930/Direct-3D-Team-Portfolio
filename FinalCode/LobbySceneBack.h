#pragma once

#include "Back.h"

class CLobbySceneBack : public CBack
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CLobbySceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CLobbySceneBack();
};
