#pragma once

#include "SignUI.h"

class CSockSign : public CSignUI
{
private:
	// Item
	Item* m_pItem;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSockSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CSockSign();
};
