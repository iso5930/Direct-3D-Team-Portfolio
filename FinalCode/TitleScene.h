#pragma once

#include "Scene.h"

class CTitleScene : public CScene
{
private:
	// Time
	float m_fTime;

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
	explicit CTitleScene(CScene* _pScene);
	virtual ~CTitleScene();
};
