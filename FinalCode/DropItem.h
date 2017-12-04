#pragma once

#include "Object.h"

class CDropMessage;

class CDropItem : public CObject
{
private:
	// Item
	Item* m_pItem;

	// Get
	bool m_bGet;

	// IsOver
	bool m_bIsOver;

	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// Acc
	float m_fAcc;

	// StartY
	float m_fStartY;

	// Ray
	Ray m_ray;

	// Vertex
	D3DXVECTOR3 m_vVertex[4];

	// DropMessage
	CDropMessage* m_pDropMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetItem
	Item* GetItem() { return m_pItem; }

	// Get
	void Get() { m_bGet = true; }

	// IsOver
	bool IsOver() { return m_bIsOver; }

	// DisOver
	void DisOver();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

public:
	explicit CDropItem(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CDropItem();
};
