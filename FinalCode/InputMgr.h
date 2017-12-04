#pragma once

class CInputMgr
{
private:
	// Input
	LPDIRECTINPUT8 m_pInput;

	// KeyBoard
	LPDIRECTINPUTDEVICE8 m_pKeyBoard;

	// Mouse
	LPDIRECTINPUTDEVICE8 m_pMouse;

private:
	// Enable
	bool m_bEnable;

	// KeyState
	BYTE m_byCurKeyState[256];
	BYTE m_byPreKeyState[256];
	BYTE m_byCurKeyStateEx[256];
	BYTE m_byPreKeyStateEx[256];
	bool m_bKeyStop[256];
	DWORD m_dwKeyPriority[256];

	// MouseState
	DIMOUSESTATE m_CurMouseState;
	DIMOUSESTATE m_PreMouseState;
	DIMOUSESTATE m_CurMouseStateEx;
	DIMOUSESTATE m_PreMouseStateEx;
	bool m_bMouseStop[3];
	DWORD m_dwMousePriority[3];

	// MousePos
	POINT m_ptMousePos;
	D3DXVECTOR3 m_vMousePos;

	// PickPos
	D3DXVECTOR3 m_vPickPos;
	Ray m_ray;
	bool m_bFind;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	bool KeyDown(BYTE _byDIKState);
	bool KeyPress(BYTE _byDIKState);
	bool KeyUp(BYTE _byDIKState);
	DWORD KeyPriority(BYTE _byDIKState);
	void KeyInvalidate(BYTE _byDIKState);
	void KeyInvalidate();
	void KeyStop(byte _byDIKState);
	void KeyStop();

public:
	bool MouseDown(BYTE _byDIMState);
	bool MousePress(BYTE _byDIMState);
	bool MouseUp(BYTE _byDIMState);
	DWORD MousePriority(BYTE _byDIMState);
	void MousePosInvalidate();
	void MouseInvalidate(BYTE _byDIMState);
	void MouseInvalidate();
	void MouseStop(BYTE _byDIMState);
	void MouseStop();
	long MouseMove(BYTE _byDIMAxis);

public:
	D3DXVECTOR3* GetMousePos() { return &m_vMousePos; }
	D3DXVECTOR3* GetPickPos() { return (m_bFind ? &m_vPickPos : NULL); }

	void Enable() { m_bEnable = true; }
	void Disable() { m_bEnable = false; }

private:
	DECLARE_SINGLETON(CInputMgr)

private:
	explicit CInputMgr();
	~CInputMgr();
};