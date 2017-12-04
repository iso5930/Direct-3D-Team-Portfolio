#include "StdAfx.h"
#include "UpdateMgr.h"

IMPLEMENT_SINGLETON(CUpdateMgr)

CUpdateMgr::CUpdateMgr()
{
}

CUpdateMgr::~CUpdateMgr()
{
	Release();
}

void CUpdateMgr::Initialize()
{
}

int CUpdateMgr::Update()
{
	sort(m_ObjectVec[UPDATE_TYPE_UI].begin(), m_ObjectVec[UPDATE_TYPE_UI].end(), UpdateCompare);

	for(int i = 0; i < UPDATE_TYPE_END; ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
			m_ObjectVec[i][j]->Update();
	}

	return 0;
}

void CUpdateMgr::Render()
{
}

void CUpdateMgr::Release()
{
	for(int i = 0; i < UPDATE_TYPE_END; ++i)
		m_ObjectVec[i].clear();
}

void CUpdateMgr::AddObject(UPDATE_TYPE _eUpdateType, CObject* _pObject)
{
	m_ObjectVec[_eUpdateType].push_back(_pObject);
}

void CUpdateMgr::RemoveObject(UPDATE_TYPE _eUpdateType, CObject* _pObject)
{
	for(size_t i = 0; i < m_ObjectVec[_eUpdateType].size(); ++i)
	{
		if(m_ObjectVec[_eUpdateType][i] == _pObject)
		{
			m_ObjectVec[_eUpdateType][i] = m_ObjectVec[_eUpdateType][m_ObjectVec[_eUpdateType].size() - 1];
			m_ObjectVec[_eUpdateType].pop_back();
		}
	}
}