#pragma once

class CLayer;
class CBack;

class CScene
{
protected:
	// Mode
	DWORD m_dwMode;

	// Thread
	HANDLE m_hThread;

	// LoadBack
	CBack* m_pLoadBack;

	// Layer
	CLayer* m_pLayer[LAYER_TYPE_END];

public:
	virtual void Initialize() = 0;
	virtual CScene* Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

private:
	static UINT WINAPI LoadThread(LPVOID _pParam);

protected:
	virtual CScene* UpdateLoad() = 0;
	virtual CScene* UpdateComplete() = 0;
	virtual CScene* UpdatePlay() = 0;

public:
	// GetLayer
	CLayer* GetLayer(LAYER_TYPE _eLayerType);

	// Destroy
	void Destroy();

public:
	explicit CScene(CScene* _pScene);
	virtual ~CScene();
};