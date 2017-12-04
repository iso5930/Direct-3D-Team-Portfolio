#pragma once

#include "Object.h"

class CRenderCom;
class CUpdateCom;

class CBack : public CObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszTexKey);
	virtual ~CBack();
};
