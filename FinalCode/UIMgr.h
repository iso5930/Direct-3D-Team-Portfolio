#pragma once

class CUIMgr
{
private:
	// Enable
	bool m_bEnable;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// Enable
	void Enable();

	// Disable
	void Disable();

	// GetWindow
	CObject* GetWindow(WINDOW_TYPE _eWindowType);

	// NewWindow
	bool NewWindow(WINDOW_TYPE _eWindowType, int _iIndex = -1, SLOT_ID _eSlotID = SLOT_ID_END);

	// DeleteWindow
	bool DeleteWindow(WINDOW_TYPE _eWindowType);

	// DeleteLeftWindow
	bool DeleteLeftWindow();

	// DeleteRightWindow
	bool DeleteRightWindow();

	// DeleteCenterWindow
	bool DeleteCenterWindow();

	// DeleteAllWindow
	bool DeleteAllWindow();

	// RenewWindow
	bool RenewWindow(WINDOW_TYPE _eWindowType);

	// CreateTextMessage
	bool CreateTextMessage(TCHAR* _tszText);

private:
	DECLARE_SINGLETON(CUIMgr)

public:
	explicit CUIMgr();
	~CUIMgr();
};
