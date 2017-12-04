#pragma once

#include "Camera.h"

class CPlayerCamera : public CCamera
{
private:
	// Dist
	float m_fDist;

	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CPlayerCamera(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwIndex);
	virtual ~CPlayerCamera();
};
