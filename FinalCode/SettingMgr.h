#pragma once

class CSettingMgr
{
private:
	// RenderMode
	DWORD m_dwRenderMode;

	// GameMode
	DWORD m_dwGameMode;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// Begin
	void Begin();

	// End
	void End();

public: ////////////////////////////////////////////////////////////////////////// Graphic
	// SetBlurMode
	void SetBlurMode(DWORD _dwBlurMode);

	// SetShadowMode
	void SetShadowMode(DWORD _dwShadowMode);

	// SetFogMode
	void SetFogMode(DWORD _dwFogMode);

	// SetHDRMode
	void SetHDRMode(DWORD _dwHDRMode);

	// SetSSAOMode
	void SetSSAOMode(DWORD _dwSSAOMode);

	// SetDistortionMode
	void SetDistortionMode(DWORD _dwDistortionMode);

	// GetRenderMode
	DWORD GetRenderMode() { return m_dwRenderMode; }

public: ////////////////////////////////////////////////////////////////////////// Game
	// AddGameMode
	void AddGameMode(DWORD _dwGameMode);

	// RemoveGameMode
	void RemoveGameMode(DWORD _dwGameMode);

	// GetGameMode
	DWORD GetGameMode() { return m_dwGameMode; }

private:
	DECLARE_SINGLETON(CSettingMgr)

public:
	explicit CSettingMgr();
	~CSettingMgr();
};
