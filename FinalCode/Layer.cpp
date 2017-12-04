#include "Stdafx.h"
#include "Layer.h"

CLayer::CLayer(CScene* _pScene, CLayer* _pLayer)
{
	m_pScene = _pScene;

	if(_pLayer == NULL)
		return;

	for(size_t i = 0; i < _pLayer->m_ObjectVec[OBJ_NONAMED].size(); ++i)
	{
		CObject* pObject = _pLayer->m_ObjectVec[OBJ_NONAMED][i];

		if(pObject->GetObjType() == OBJ_TYPE_STATIC)
			AddObject(pObject);
	}

	for(size_t i = 0; i < _pLayer->m_ObjectVec[OBJ_NAMED].size(); ++i)
	{
		CObject* pObject = _pLayer->m_ObjectVec[OBJ_NAMED][i];

		if(pObject->GetObjType() == OBJ_TYPE_STATIC)
			AddObject(pObject);
	}
}

CLayer::~CLayer()
{
	Release();
}

void CLayer::Initialize()
{
}

int CLayer::Update()
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
		{
			if(m_ObjectVec[i][j]->IsDestroy())
			{
				delete m_ObjectVec[i][j];

				for(size_t k = j + 1; k < m_ObjectVec[i].size(); ++k)
					m_ObjectVec[i][k - 1] = m_ObjectVec[i][k];

				//m_ObjectVec[i][j] = m_ObjectVec[i][m_ObjectVec[i].size() - 1];
				m_ObjectVec[i].pop_back();
				--j;
			}
		}
	}

	return 0;
}

void CLayer::Render()
{
}

void CLayer::Release()
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
		{
			if(m_ObjectVec[i][j]->GetObjType() != OBJ_TYPE_STATIC)
				delete m_ObjectVec[i][j];
		}

		m_ObjectVec[i].clear();
	}
}

void CLayer::AddObject(CObject* _pObject)
{
	_pObject->SetLayer(this);

	if(_pObject->GetObjKey() == NULL)
		m_ObjectVec[OBJ_NONAMED].push_back(_pObject);
	else
		m_ObjectVec[OBJ_NAMED].push_back(_pObject);
}

void CLayer::AddObject(CObject* _pObject, LAYER_TYPE _eLayerType)
{
	m_pScene->GetLayer(_eLayerType)->AddObject(_pObject);
}

void CLayer::RemoveObject(CObject* _pObject)
{
	for(size_t i = 0; i < m_ObjectVec[OBJ_NAMED].size(); ++i)
	{
		if(m_ObjectVec[OBJ_NAMED][i] == _pObject)
		{
			m_ObjectVec[OBJ_NAMED][i] = m_ObjectVec[OBJ_NAMED][m_ObjectVec[OBJ_NAMED].size() - 1];
			delete _pObject;
			m_ObjectVec[OBJ_NAMED].pop_back();
		}
	}
}

void CLayer::RemoveObject(CObject* _pObject, LAYER_TYPE _eLayerType)
{
	m_pScene->GetLayer(_eLayerType)->RemoveObject(_pObject);
}

void CLayer::FindObject(CObject*& _pFindObject, TCHAR* _tszObjKey)
{
	if(_pFindObject != NULL)
		return;

	for(size_t i = 0; i < m_ObjectVec[OBJ_NAMED].size(); ++i)
	{
		if(_tcscmp(_tszObjKey, m_ObjectVec[OBJ_NAMED][i]->GetObjKey()) == 0)
		{
			_pFindObject = m_ObjectVec[OBJ_NAMED][i];
			break;
		}
	}
}

void CLayer::FindObject(CObject*& _pFindObject, TCHAR* _tszObjKey, LAYER_TYPE _eLayerType)
{
	if(_pFindObject != NULL)
		return;

	m_pScene->GetLayer(_eLayerType)->FindObject(_pFindObject, _tszObjKey);
}

void CLayer::FindObjects(vector<CObject*>& _pFindObjects, TCHAR* _tszObjKey)
{
	for(size_t i = 0; i < m_ObjectVec[OBJ_NAMED].size(); ++i)
	{
		if(_tcscmp(_tszObjKey, m_ObjectVec[OBJ_NAMED][i]->GetObjKey()) == 0)
			_pFindObjects.push_back(m_ObjectVec[OBJ_NAMED][i]);
	}
}

void CLayer::FindObjects(vector<CObject*>& _pFindObjects, TCHAR* _tszObjKey, LAYER_TYPE _eLayerType)
{
	m_pScene->GetLayer(_eLayerType)->FindObjects(_pFindObjects, _tszObjKey);
}

void CLayer::Destroy()
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		while(m_ObjectVec[i].size() != 0)
		{
			delete (*m_ObjectVec[i].begin());
			m_ObjectVec[i].erase(m_ObjectVec[i].begin());
		}
	}
}