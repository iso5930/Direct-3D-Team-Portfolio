#pragma once

class CObject;

class CUpdateMgr
{
private:
	// Object Vector
	vector<CObject*> m_ObjectVec[UPDATE_TYPE_END];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	void AddObject(UPDATE_TYPE _eUpdateType, CObject* _pObject);
	void RemoveObject(UPDATE_TYPE _eUpdateType, CObject* _pObject);

private:
	DECLARE_SINGLETON(CUpdateMgr)

private:
	explicit CUpdateMgr();
	~CUpdateMgr();
};

inline bool UpdateCompare(CObject* _pLeft, CObject* _pRight)
{
	return ((CUpdateCom*)_pLeft->GetComponent(COM_TYPE_UPDATE))->m_dwPriority > ((CUpdateCom*)_pRight->GetComponent(COM_TYPE_UPDATE))->m_dwPriority;
}