#pragma once

#include "SignUI.h"

class CItemPannelSign : public CSignUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemPannelSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CItemPannelSign();
};
