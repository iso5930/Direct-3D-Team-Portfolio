#pragma once

#include "Component.h"

class CRenderCom : public CComponent
{
private:
	// RenderType
	RENDER_TYPE m_eRenderType;

public:
	// Priority
	DWORD m_dwPriority;

	// Pass
	DWORD m_dwPass;

	// Color
	D3DXVECTOR4 m_vColor;

	// RimColor
	D3DXVECTOR4 m_vRimColor;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CRenderCom(RENDER_TYPE _eRenderType);
	virtual ~CRenderCom();
};