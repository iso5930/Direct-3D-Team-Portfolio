#pragma once

#include "MessageUI.h"

class CDamageMessage : public CMessageUI
{
private:
	// Width
	int m_iWidth;

	// Height
	int m_iHeight;

	// Time
	float m_fTime;

	// Color
	D3DXCOLOR m_dwColor;

	// Velo
	D3DXVECTOR2 m_vVelo;

	// Move
	D3DXVECTOR2 m_vMove;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDamageMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iDamage, D3DXCOLOR* _pColor);
	virtual ~CDamageMessage();
};
