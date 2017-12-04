#pragma once

class CScene;

class CSceneMgr
{
private:
	// Destroy
	bool m_bDestroy;

	// Scene
	CScene* m_pScene;

	// NextScene
	CScene* m_pNextScene;

	// InPlay
	bool m_bInPlay;

	// NextPos
	D3DXVECTOR3 m_vNextPos;

	// NextAngle
	D3DXVECTOR3 m_vNextAngle;

	// NextSize
	D3DXVECTOR3 m_vNextSize;

public:
	void Initialize(CScene* _pScene);
	int Update();
	void Render();
	void Release();

public:
	// Destroy
	void Destroy() { m_bDestroy = true; }

	// GetScene
	CScene* GetScene() { return m_pScene; }

	// SetNextScene
	void SetNextScene(CScene* _pNextScene, bool _bInPlay, D3DXVECTOR3* _pNextPos = NULL, D3DXVECTOR3* _pNextAngle = NULL, D3DXVECTOR3* _pNextSize = NULL);

private:
	DECLARE_SINGLETON(CSceneMgr)

private:
	explicit CSceneMgr();
	~CSceneMgr();
};