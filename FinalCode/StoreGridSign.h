#pragma once

#include "SignUI.h"

class CStoreGridSign : public CSignUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CStoreGridSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CStoreGridSign();
};
