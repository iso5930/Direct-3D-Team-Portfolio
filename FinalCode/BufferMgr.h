#pragma once

class CBuffer;

class CBufferMgr
{
private:
	// BufferMap
	unordered_map<TCHAR*, CBuffer*> m_BufferMap;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// AddBuffer
	void AddBuffer(TCHAR* _tszBufKey, CBuffer* _pBuffer);

	// RemoveBuffer
	void RemoveBuffer(TCHAR* _tszBufKey);

	// GetBuffer
	CBuffer* GetBuffer(TCHAR* _tszBufKey);

private:
	DECLARE_SINGLETON(CBufferMgr)

private:
	explicit CBufferMgr();
	~CBufferMgr();
};