#pragma once

class CScene;
class CObject;

class CLayer
{
private:
	enum { OBJ_NAMED, OBJ_NONAMED, OBJ_END };

private:
	// Scene
	CScene* m_pScene;

	// ObjectVec
	vector<CObject*> m_ObjectVec[OBJ_END];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// AddObject
	void AddObject(CObject* _pObject);
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayerType);

	// RemoveObject
	void RemoveObject(CObject* _pObject);
	void RemoveObject(CObject* _pObject, LAYER_TYPE _eLayerType);

	// FindObject
	void FindObject(CObject*& _pFindObject, TCHAR* _tszObjKey);
	void FindObject(CObject*& _pFindObject, TCHAR* _tszObjKey, LAYER_TYPE _eLayerType);

	// FindObjects
	void FindObjects(vector<CObject*>& _pFindObjects, TCHAR* _tszObjKey);
	void FindObjects(vector<CObject*>& _pFindObjects, TCHAR* _tszObjKey, LAYER_TYPE _eLayerType);

	// Destroy
	void Destroy();

public:
	explicit CLayer(CScene* _pScene, CLayer* _pLayer);
	~CLayer();
};