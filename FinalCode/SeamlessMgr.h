#pragma once

class CSeamlessMgr
{
private:
	// Enable
	bool m_bEnable;

	// Destroy
	bool m_bDestroy;

	// Zone
	int m_iZone;

	// MapKey
	TCHAR m_tszMapKey[MIN_STR];

	// LoadThread
	HANDLE m_hLoadThread;

	// ClearThread
	HANDLE m_hClearThread;

	// CS
	LPCRITICAL_SECTION m_pInCS;
	LPCRITICAL_SECTION m_pOutCS;

	// Mode
	int m_iMode;

	// NodeMap
	unordered_map<int, vector<int>> m_NodeMap;

	// ClearVec
	vector<TCHAR*> m_ClearVec[2];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public: ////////////////////////////////////////////////////////////////////////// OutFunction
	// Enable
	void Enable();

	// Disable
	void Disable();

	// AddNode
	void AddNode(int _iKey, int _iZone);

	// RemoveMapBuffer
	void RemoveMapBuffer(TCHAR* _tszBufKey);

private: ////////////////////////////////////////////////////////////////////////// InFunction
	void WaitClearThread();
	void WaitOutCSInClearThread();
	void CompleteClearThread();

	void WaitLoadThread();
	void WaitOutCSInLoadThread();
	void CompleteLoadThread();

private: ////////////////////////////////////////////////////////////////////////// Thread
	// ClearThread & Clear
	static UINT WINAPI ClearThread(LPVOID _pParam);
	void Clear();

	// LoadThread & Load
	static UINT WINAPI LoadThread(LPVOID _pParam);
	void Load();

private:
	DECLARE_SINGLETON(CSeamlessMgr)

public:
	explicit CSeamlessMgr();
	~CSeamlessMgr();
};
