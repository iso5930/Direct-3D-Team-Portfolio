#pragma once

class CLayer;
class CComponent;
class CTransformCom;

class CObject
{
protected:
	// Destroy
	bool m_bDestroy;

	// Layer
	CLayer* m_pLayer;

	// ObjKey
	TCHAR* m_tszObjKey;

	// ObjType
	OBJ_TYPE m_eObjType;

	// Component
	CComponent* m_pComponent[COM_TYPE_END];

	// TransformCom
	CTransformCom* m_pTransformCom;

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	// Destroy
	virtual void Destroy();

public:
	// IsDestroy
	bool IsDestroy() { return m_bDestroy; }

	// Set Layer
	void SetLayer(CLayer* _pLayer) { m_pLayer = _pLayer; }

	// Get Layer
	CLayer* GetLayer() { return m_pLayer; }

	// Add Component
	void AddComponent(CComponent* _pComponent);

	// Remove Componenet
	void RemoveComponent(COM_TYPE _eComType);

	// GetObjKey
	TCHAR* GetObjKey() { return m_tszObjKey; }

	// GetObjType
	OBJ_TYPE GetObjType() { return m_eObjType; }

	// Get Component
	CComponent* GetComponent(COM_TYPE _eComType) { return m_pComponent[_eComType]; }

public:
	explicit CObject(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CObject();
};