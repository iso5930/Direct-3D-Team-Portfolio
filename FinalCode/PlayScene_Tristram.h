#pragma once

#include "Scene.h"

class CPlayScene_Tristram : public CScene
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
	explicit CPlayScene_Tristram(CScene* _pScene);
	virtual ~CPlayScene_Tristram();
};
