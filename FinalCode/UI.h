#pragma once

#include "Object.h"

class CMaterialCom;

class CUI : public CObject
{
protected:
	// State
	DWORD m_dwState;

	// BackTexture
	LPDIRECT3DBASETEXTURE9 m_pBackTexture;

	// MaterialCom
	CMaterialCom* m_pMaterialCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void SetState(DWORD _dwState);
	void AddState(DWORD _dwState);
	void RemoveState(DWORD _dwState);
	bool IsOver();
	bool IsLDown();
	bool IsLPress();
	bool IsLUp();
	bool IsRDown();
	bool IsRPress();
	bool IsRUp();

public:
	explicit CUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CUI();
};
