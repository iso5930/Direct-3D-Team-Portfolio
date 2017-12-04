#include "Stdafx.h"
#include "InputMgr.h"

IMPLEMENT_SINGLETON(CInputMgr)

CInputMgr::CInputMgr()
{
	// Input
	m_pInput = NULL;

	// KeyBoard
	m_pKeyBoard = NULL;

	// Mouse
	m_pMouse = NULL;

	// Enable
	m_bEnable = false;

	// Key State
	ZeroMemory(m_byCurKeyState, sizeof(BYTE) * 256);
	ZeroMemory(m_byPreKeyState, sizeof(BYTE) * 256);
	ZeroMemory(m_byCurKeyStateEx, sizeof(BYTE) * 256);
	ZeroMemory(m_byPreKeyStateEx, sizeof(BYTE) * 256);
	ZeroMemory(m_bKeyStop, sizeof(m_bKeyStop));
	ZeroMemory(m_dwKeyPriority, sizeof(DWORD) * 256);

	// Mouse State
	ZeroMemory(&m_CurMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_PreMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_CurMouseStateEx, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_PreMouseStateEx, sizeof(DIMOUSESTATE));
	ZeroMemory(m_bMouseStop, sizeof(m_bMouseStop));
	ZeroMemory(m_dwMousePriority, sizeof(m_dwMousePriority));

	// Mouse Position
	ZeroMemory(&m_ptMousePos, sizeof(POINT));
	ZeroMemory(&m_vMousePos, sizeof(D3DXVECTOR3));

	// Pick Position
	ZeroMemory(&m_vPickPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_ray, sizeof(Ray));
	m_bFind = false;
}

CInputMgr::~CInputMgr()
{
	Release();
}

void CInputMgr::Initialize()
{
	// Input 持失
	if(FAILED(DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		cout << "DirectInput8Create() Error!" << endl;
		return;
	}

	// KeyBoard 持失
	if(FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, NULL)))
	{
		cout << "CreateDevice() Error!" << endl;
		return;
	}

	/*m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);*/
	if(FAILED(m_pKeyBoard->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		cout << "SetCooperativeLevel() Error!" << endl;
		return;
	}

	if(FAILED(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
	{
		cout << "SetDataFormat() Error!" << endl;
		return;
	}

	m_pKeyBoard->Acquire();

	// Mouse 持失
	if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
	{
		cout << "CreateDevice() Error!" << endl;
		return;
	}
	if(FAILED(m_pMouse->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		cout << "SetCooperativeLevel() Error!" << endl;
		return;
	}
	if(FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		cout << "SetDataFormat() Error!" << endl;
		return;
	}

	m_pMouse->Acquire();
}

int CInputMgr::Update()
{
	// State
	memcpy_s(m_byPreKeyState, sizeof(BYTE) * 256, m_byCurKeyState, sizeof(BYTE) * 256);
	memcpy_s(&m_PreMouseState, sizeof(DIMOUSESTATE), &m_CurMouseState, sizeof(DIMOUSESTATE));

	m_pKeyBoard->GetDeviceState(sizeof(BYTE) * 256, m_byCurKeyState);
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurMouseState);

	memcpy_s(m_byCurKeyStateEx, sizeof(BYTE) * 256, m_byCurKeyState, sizeof(BYTE) * 256);
	memcpy_s(&m_CurMouseStateEx, sizeof(DIMOUSESTATE), &m_CurMouseState, sizeof(DIMOUSESTATE));

	memcpy_s(m_byPreKeyStateEx, sizeof(BYTE) * 256, m_byPreKeyState, sizeof(BYTE) * 256);
	memcpy_s(&m_PreMouseStateEx, sizeof(DIMOUSESTATE), &m_PreMouseState, sizeof(DIMOUSESTATE));

	// KeyStop
	for(int i = 0; i < 256; ++i)
	{
		if(m_bKeyStop[i])
		{
			if(!m_byCurKeyStateEx[i] && !m_byPreKeyStateEx[i])
				m_bKeyStop[i] = false;

			m_byCurKeyStateEx[i] = 0;
			m_byPreKeyStateEx[i] = 0;
		}
	}

	// KeyPriority
	for(int i = 0; i < 256; ++i)
	{
		if(m_byCurKeyState[i] && !m_byPreKeyState[i])
			m_dwKeyPriority[i] = 0;
		else if(m_byCurKeyState[i] && m_byPreKeyState[i])
			m_dwKeyPriority[i] += 1;
	}

	// MouseStop
	for(int i = 0; i < 3; ++i)
	{
		if(m_bMouseStop[i])
		{
			if(!m_CurMouseStateEx.rgbButtons[i] && !m_PreMouseStateEx.rgbButtons[i])
				m_bMouseStop[i] = false;

			m_CurMouseStateEx.rgbButtons[i] = 0;
			m_PreMouseStateEx.rgbButtons[i] = 0;
		}
	}

	// Mouse Priority
	for(int i = 0; i < 3; ++i)
	{
		if(m_CurMouseState.rgbButtons[i] && !m_PreMouseState.rgbButtons[i])
			m_dwMousePriority[i] = 0;
		else if(m_CurMouseState.rgbButtons[i] && m_PreMouseState.rgbButtons[i])
			m_dwMousePriority[i] += 1;
	}

	// Mouse Position
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(g_hWnd, &m_ptMousePos);

	m_vMousePos.x = float(m_ptMousePos.x);
	m_vMousePos.y = float(m_ptMousePos.y);

	// PickPos
	ZeroMemory(&m_vPickPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_ray, sizeof(Ray));
	m_bFind = false;

	// Check Enable
	if(!m_bEnable)
		return 0;

	// Player
	CObject* pPlayer = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_PLAYER)->FindObject(pPlayer, _T("Player"));
	if(pPlayer == NULL)
		return 0;

	// PathFindCom
	CPathFindCom* pPathFindCom = (CPathFindCom*)pPlayer->GetComponent(COM_TYPE_PATH_FIND);
	if(pPathFindCom->m_pCell == NULL)
		return 0;

	vector<CNaviCell*> CellVec;
	DWORD dwFront = 0;

	// Start Push
	CellVec.push_back(pPathFindCom->m_pCell);

	// ScreenToWorld
	ScreenToWorld(&m_ray, &m_vMousePos, CCameraMgr::GetInstance()->GetProj(), CCameraMgr::GetInstance()->GetInvView());

	// Find Cell
	CNaviCell* pCurCell = NULL;
	float u, v, dist;
	while(dwFront < CellVec.size() && dwFront < 1000)
	{
		pCurCell = CellVec[dwFront++];
		pCurCell->m_bVisited = true;
		
		if(D3DXIntersectTri(&(pCurCell->m_vPoint[0]), &(pCurCell->m_vPoint[1]), &(pCurCell->m_vPoint[2]), &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
		{
			m_vPickPos = pCurCell->m_vPoint[0] + u * (pCurCell->m_vPoint[1] - pCurCell->m_vPoint[0]) + v * (pCurCell->m_vPoint[2] - pCurCell->m_vPoint[0]);
			m_bFind = true;
			break;
		}

		if(pCurCell->m_pLink[0] != NULL && pCurCell->m_pLink[0]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[0]);
		if(pCurCell->m_pLink[1] != NULL && pCurCell->m_pLink[1]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[1]);
		if(pCurCell->m_pLink[2] != NULL && pCurCell->m_pLink[2]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[2]);
	}

	for(size_t i = 0; i < CellVec.size(); ++i)
		CellVec[i]->m_bVisited = false;
	CellVec.clear();

	return 0;
}

void CInputMgr::Render()
{
}

void CInputMgr::Release()
{
	if(m_pMouse != NULL)
	{
		m_pMouse->Release();
		m_pMouse = NULL;
	}

	if(m_pKeyBoard != NULL)
	{
		m_pKeyBoard->Release();
		m_pKeyBoard = NULL;
	}

	if(m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

bool CInputMgr::KeyDown(BYTE _byDIKState)
{
	if(m_byCurKeyStateEx[_byDIKState] && !m_byPreKeyStateEx[_byDIKState])
		return true;

	return false;
}

bool CInputMgr::KeyPress(BYTE _byDIKState)
{
	if(m_byCurKeyStateEx[_byDIKState] && m_byPreKeyStateEx[_byDIKState])
		return true;

	return false;
}

bool CInputMgr::KeyUp(BYTE _byDIKState)
{
	if(!m_byCurKeyStateEx[_byDIKState] && m_byPreKeyStateEx[_byDIKState])
		return true;

	return false;
}

DWORD CInputMgr::KeyPriority(BYTE _byDIKState)
{
	if(m_byCurKeyStateEx[_byDIKState] && !m_byPreKeyStateEx[_byDIKState])
		return m_dwKeyPriority[_byDIKState];
	else if(m_byCurKeyStateEx[_byDIKState] && m_byPreKeyStateEx[_byDIKState])
		return m_dwKeyPriority[_byDIKState];
	
	return 0xFFFFFFFF;
}

void CInputMgr::KeyInvalidate(BYTE _byDIKState)
{
	m_byCurKeyStateEx[_byDIKState] = 0;
	m_byPreKeyStateEx[_byDIKState] = 0;
}

void CInputMgr::KeyInvalidate()
{
	ZeroMemory(m_byCurKeyStateEx, sizeof(BYTE) * 256);
	ZeroMemory(m_byPreKeyStateEx, sizeof(BYTE) * 256);
}

void CInputMgr::KeyStop(byte _byDIKState)
{
	m_bKeyStop[_byDIKState] = true;
	m_byCurKeyStateEx[_byDIKState] = 0;
	m_byPreKeyStateEx[_byDIKState] = 0;
}

void CInputMgr::KeyStop()
{
	memset(m_bKeyStop, 1, sizeof(m_bKeyStop));
	ZeroMemory(m_byCurKeyStateEx, sizeof(BYTE) * 256);
	ZeroMemory(m_byPreKeyStateEx, sizeof(BYTE) * 256);
}

bool CInputMgr::MouseDown(BYTE _byDIMState)
{
	if(m_CurMouseStateEx.rgbButtons[_byDIMState] && !m_PreMouseStateEx.rgbButtons[_byDIMState])
		return true;

	return false;
}

bool CInputMgr::MousePress(BYTE _byDIMState)
{
	if(m_CurMouseStateEx.rgbButtons[_byDIMState] && m_PreMouseStateEx.rgbButtons[_byDIMState])
		return true;

	return false;
}

bool CInputMgr::MouseUp(BYTE _byDIMState)
{
	if(!m_CurMouseStateEx.rgbButtons[_byDIMState] && m_PreMouseStateEx.rgbButtons[_byDIMState])
		return true;

	return false;
}

DWORD CInputMgr::MousePriority(BYTE _byDIMState)
{
	if(m_CurMouseStateEx.rgbButtons[_byDIMState] && !m_PreMouseStateEx.rgbButtons[_byDIMState])
		return m_dwMousePriority[_byDIMState];
	else if(m_CurMouseStateEx.rgbButtons[_byDIMState] && m_PreMouseStateEx.rgbButtons[_byDIMState])
		return m_dwMousePriority[_byDIMState];
	
	return 0xFFFFFFFF;
}

void CInputMgr::MousePosInvalidate()
{
	ZeroMemory(&m_vMousePos, sizeof(D3DXVECTOR3));
}

void CInputMgr::MouseInvalidate(BYTE _byDIMState)
{
	m_CurMouseStateEx.rgbButtons[_byDIMState] = 0;
	m_PreMouseStateEx.rgbButtons[_byDIMState] = 0;
}

void CInputMgr::MouseInvalidate()
{
	ZeroMemory(&m_CurMouseStateEx.rgbButtons, sizeof(BYTE) * 4);
	ZeroMemory(&m_PreMouseStateEx.rgbButtons, sizeof(BYTE) * 4);
}

void CInputMgr::MouseStop(BYTE _byDIMState)
{
	m_bMouseStop[_byDIMState] = true;
	m_CurMouseStateEx.rgbButtons[_byDIMState] = 0;
	m_PreMouseStateEx.rgbButtons[_byDIMState] = 0;
}

void CInputMgr::MouseStop()
{
	memset(m_bMouseStop, 1, sizeof(m_bMouseStop));
	ZeroMemory(&m_CurMouseStateEx.rgbButtons, sizeof(BYTE) * 4);
	ZeroMemory(&m_PreMouseStateEx.rgbButtons, sizeof(BYTE) * 4);
}

long CInputMgr::MouseMove(BYTE _byDIMAxis)
{
	switch(_byDIMAxis)
	{
	case DIM_X:
		return m_CurMouseStateEx.lX;

	case DIM_Y:
		return m_CurMouseStateEx.lY;

	case DIM_Z:
		return m_CurMouseStateEx.lZ;
	}

	return 0;
}