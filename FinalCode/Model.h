#pragma once

#include "Object.h"

class CModel : public CObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CModel(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBoots, TCHAR* _tszHair, TCHAR* _tszHands, TCHAR* _tszPants, TCHAR* _tszUpper);
	virtual ~CModel();
};
