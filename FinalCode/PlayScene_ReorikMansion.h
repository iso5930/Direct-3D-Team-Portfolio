#pragma once

#include "Scene.h"

class CPlayScene_ReorikMansion : public CScene
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
	explicit CPlayScene_ReorikMansion(CScene* _pScene);
	virtual ~CPlayScene_ReorikMansion();
};
