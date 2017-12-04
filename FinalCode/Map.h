#pragma once

#include "Object.h"

class CMap : public CObject
{
private:
	// BufKey
	TCHAR m_tszBufKey[MIN_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// BufKey
	TCHAR* GetBufKey() { return m_tszBufKey; }

public:
	explicit CMap(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBufKey, TCHAR* _tszPath, TCHAR* _tszFile);
	virtual ~CMap();
};