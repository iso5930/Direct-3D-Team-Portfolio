#pragma once

#include "SignUI.h"

class CStatMarkSign : public CSignUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CStatMarkSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CStatMarkSign();
};
