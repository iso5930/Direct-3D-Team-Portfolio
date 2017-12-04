#pragma once

#include "StaticProb.h"

class CScene;

class CGate : public CStaticProb
{
private:
	// MapKey
	TCHAR m_tszMapKey[MIN_STR];

	// Pos
	D3DXVECTOR3 m_vPos;

	// Angle
	D3DXVECTOR3 m_vAngle;

	// Size
	D3DXVECTOR3 m_vSize;

	// SceneType
	SCENE_TYPE m_eSceneType;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Event
	virtual void Event();

	// EventEnd
	virtual void EventEnd();

public:
	explicit CGate(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText, TCHAR* _tszMapKey, D3DXVECTOR3* _pPos, D3DXVECTOR3* _pAngle, D3DXVECTOR3* _pSize, SCENE_TYPE _eSceneType);
	virtual ~CGate();
};
