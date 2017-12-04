#include "StdAfx.h"
#include "SettingMgr.h"

IMPLEMENT_SINGLETON(CSettingMgr)

CSettingMgr::CSettingMgr()
{
	// RenderMode
	m_dwRenderMode = 0;

	// GameMode
	m_dwGameMode = 0;
}

CSettingMgr::~CSettingMgr()
{
	Release();
}

void CSettingMgr::Initialize()
{
}

int CSettingMgr::Update()
{
	return 0;
}

void CSettingMgr::Render()
{
}

void CSettingMgr::Release()
{
}

// Begin
void CSettingMgr::Begin()
{
	// RenderMode
	m_dwRenderMode = CDataMgr::GetInstance()->GetRenderMode();

	// GameMode
	m_dwGameMode = CDataMgr::GetInstance()->GetGameMode();
}

// End
void CSettingMgr::End()
{
	// RenderMode
	m_dwRenderMode = 0;

	// GameMode
	m_dwGameMode = 0;
}

////////////////////////////////////////////////////////////////////////// Graphic
void CSettingMgr::SetBlurMode(DWORD _dwBlurMode)
{
	DWORD dw = RENDER_MODE_RADIAL_BLUR | RENDER_MODE_GAUSSIAN_BLUR | RENDER_MODE_MOTION_BLUR;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwBlurMode;
}

void CSettingMgr::SetShadowMode(DWORD _dwShadowMode)
{
	DWORD dw = RENDER_MODE_NORMAL_SHADOW | RENDER_MODE_CASCADE_SHADOW;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwShadowMode;
}

void CSettingMgr::SetFogMode(DWORD _dwFogMode)
{
	DWORD dw = RENDER_MODE_EXPONENT_FOG | RENDER_MODE_EXPONENT_SQUARE_FOG | RENDER_MODE_HEIGHT_FOG;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwFogMode;
}

void CSettingMgr::SetHDRMode(DWORD _dwHDRMode)
{
	DWORD dw = RENDER_MODE_HDR;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwHDRMode;
}

void CSettingMgr::SetSSAOMode(DWORD _dwSSAOMode)
{
	DWORD dw = RENDER_MODE_SSAO;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwSSAOMode;
}

void CSettingMgr::SetDistortionMode(DWORD _dwDistortionMode)
{
	DWORD dw = RENDER_MODE_DISTORTION;
	m_dwRenderMode &= (~dw);
	m_dwRenderMode |= _dwDistortionMode;
}

////////////////////////////////////////////////////////////////////////// Game
void CSettingMgr::AddGameMode(DWORD _dwGameMode)
{
	m_dwGameMode |= _dwGameMode;
}

void CSettingMgr::RemoveGameMode(DWORD _dwGameMode)
{
	m_dwGameMode &= (~_dwGameMode);
}