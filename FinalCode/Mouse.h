#pragma once

#include "Object.h"

class CItemSign;
class CMaterialCom;

class CMouse : public CObject
{
private:
	// Texture
	// 0(Arrow), 1(Inven), 2(Equip), 3(Storage), 4(Store), 5(Decompose), 6(FollowerEquip)
	LPDIRECT3DBASETEXTURE9 m_pTexture[7];

	// PickType
	int m_iPickType;

	// MouseOverType
	MOUSE_OVER_TYPE m_eMouseOverType;

	// Select
	int m_iSelect;

	// ItemSign
	CItemSign* m_pItemSign;

	// OverObject
	CObject* m_pOverObject;

	// MaterialCom
	CMaterialCom* m_pMaterialCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	// UpdateInInventory
	void UpdateInInventory();

	// UpdateInStorage
	void UpdateInStorage();

public:
	// GetPickType
	int GetPickType() { return m_iPickType; }

	// GetOverType
	int GetMouseOverType() { return m_eMouseOverType; }

	// GetSelect
	int GetSelect() { return m_iSelect; }

	// GetOverObject
	CObject* GetOverObject() { return m_pOverObject; }

	// Pick
	void Pick(int _iPickType, int _iSelect, Item* _pItem);

	// Drop
	void Drop();

	// Over
	void Over(MOUSE_OVER_TYPE _eMouseOverType, CObject* _pOverObject);

	// GetItem
	Item* GetItem();

public:
	explicit CMouse(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMouse();
};
