#include "Stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);
	m_fDeltaTime = 0.0f;
	m_fAccTime = 0.0f;
}

CTimeMgr::~CTimeMgr()
{
	Release();
}

void CTimeMgr::Initialize()
{
}

int CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_FrameTime);

	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
		m_LastTime.QuadPart = m_FrameTime.QuadPart;

	m_fDeltaTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / float(m_CpuTick.QuadPart);
	m_FixTime = m_FrameTime;
	m_fAccTime += m_fDeltaTime;

	return 0;
}

void CTimeMgr::Render()
{
}

void CTimeMgr::Release()
{
}

float CTimeMgr::GetDeltaTime()
{
	return m_fDeltaTime;
}

float CTimeMgr::GetAccTime()
{
	return m_fAccTime;
}