#pragma once

class CDataMgr
{
private:
	// Select
	int m_iSelect;

	// CharacterNum
	int m_iCharacterNum;

	// Gold
	int m_iGold;

	// RenderMode
	DWORD m_dwRenderMode;

	// GameMode
	DWORD m_dwGameMode;

	// ID
	TCHAR m_tszID[MIN_STR];

	// PW
	TCHAR m_tszPW[MIN_STR];

	// Account
	TCHAR m_tszAccount[MAX_STR];

	// AccountArr
	Account* m_pAccountArr[10];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// GetCharacterNum
	int GetCharacterNum() { return m_iCharacterNum; }

	// SetSelect
	void SetSelect(int _iSelect) { m_iSelect = _iSelect; }

	// GetSelect
	int GetSelect() { return m_iSelect; }

	// GetAccount
	Account* GetAccount(int _iIndex) { return m_pAccountArr[_iIndex]; }

	// GetGold
	int GetGold() { return m_iGold; }

	// GetRenderMode
	DWORD GetRenderMode() { return m_dwRenderMode; }

	// GetGameMode
	DWORD GetGameMode() { return m_dwGameMode; }

	// IsGateWay
	bool IsGateWay(GATE_WAY_TYPE _eGateWayType);

	// AddGateWay
	void AddGateWay(GATE_WAY_TYPE _eGateWayType);

public:
	// Load
	int Load(TCHAR* _tszID, TCHAR* _tszPW);

	// Create
	int Create(TCHAR* _tszName, int _iGender, int _iJob);

	// Delete
	int Delete(int _iIndex);

	// Renew
	void Renew();

	// Reset
	void Reset();

	// Save
	void Save();

private:
	// Load
	void Load();

private:
	DECLARE_SINGLETON(CDataMgr)

public:
	explicit CDataMgr();
	~CDataMgr();
};
