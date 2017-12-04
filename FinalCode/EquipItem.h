#pragma once

#include "Object.h"

class CEquipItem : public CObject
{
private:
	// Item
	Item* m_pItem;

	// Bone
	Bone* m_pBone;

	// Matrix
	D3DXMATRIX m_mMatrix;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetItem
	Item* GetItem() { return m_pItem; }

	// SetMatrix
	void SetMatrix(float _fAngleX, float _fAngleY, float _fAngleZ);

public:
	explicit CEquipItem(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem, Bone* _pBone);
	virtual ~CEquipItem();
};
