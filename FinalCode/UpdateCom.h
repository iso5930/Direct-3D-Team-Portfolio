#pragma once

#include "Component.h"

class CUpdateCom : public CComponent
{
private:
	// UpdateType
	UPDATE_TYPE m_eUpdateType;

public:
	// Priority
	DWORD m_dwPriority;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CUpdateCom(UPDATE_TYPE _eUpdateType);
	virtual ~CUpdateCom();
};