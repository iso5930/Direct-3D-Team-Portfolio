#pragma once

#include "Scene.h"

class CLoadScene : public CScene
{
private:
	// LoadBack
	bool m_bLoadBack;

	// NextScene
	CScene* m_pNextScene;

	// UnloadVec
	vector<UNLOAD_TYPE> m_UnloadVec;

	// LoadVec
	vector<LOAD_TYPE> m_LoadVec;

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
	// SetNextScene
	void SetNextScene(CScene* _pScene) { m_pNextScene = _pScene; }

	// AddUnloadVec
	void AddUnloadVec(UNLOAD_TYPE _eUnloadType) { m_UnloadVec.push_back(_eUnloadType); }

	// AddLoadVec
	void AddLoadVec(LOAD_TYPE _eLoadType) { m_LoadVec.push_back(_eLoadType); }

public:
	explicit CLoadScene(CScene* _pScene, bool _bLoadBack);
	virtual ~CLoadScene();
};
