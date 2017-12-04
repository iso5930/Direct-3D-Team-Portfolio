#pragma once

class CTimeMgr
{
private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;
	float m_fDeltaTime;
	float m_fAccTime;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	float GetDeltaTime();
	float GetAccTime();

private:
	DECLARE_SINGLETON(CTimeMgr)

private:
	explicit CTimeMgr();
	~CTimeMgr();
};