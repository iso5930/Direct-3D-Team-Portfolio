#pragma once

#include "Scene.h"

class CPlayScene : public CScene
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
	explicit CPlayScene(CScene* _pScene);
	virtual ~CPlayScene();
};
