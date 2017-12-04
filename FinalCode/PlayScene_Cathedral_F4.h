#pragma once

#include "Scene.h"

class CPlayScene_Cathedral_F4 : public CScene
{
public:
	virtual void Initialize();
	virtual CScene* Update();
	virtual void Render();
	virtual void Release();

private:
	virtual CScene* UpdateLoad();
	virtual CScene* UpdateComplete();
	virtual CScene* UpdatePlay();

public:
	explicit CPlayScene_Cathedral_F4(CScene* _pScene);
	virtual ~CPlayScene_Cathedral_F4();
};
