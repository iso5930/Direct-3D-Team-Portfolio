#pragma once

#include "Back.h"

class CLoadBack : public CBack
{
private:
	// Time
	float m_fTime;

	// Dot
	int m_iDot;

	// Text
	TCHAR m_tszText[MAX_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CLoadBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CLoadBack();
};
