#include "Stdafx.h"
#include "BufferMgr.h"

IMPLEMENT_SINGLETON(CBufferMgr)

CBufferMgr::CBufferMgr()
{
}

CBufferMgr::~CBufferMgr()
{
	Release();
}

void CBufferMgr::Initialize()
{
}

int CBufferMgr::Update()
{
	return 0;
}

void CBufferMgr::Render()
{
}

void CBufferMgr::Release()
{
	unordered_map<TCHAR*, CBuffer*>::iterator Iter = m_BufferMap.begin();
	unordered_map<TCHAR*, CBuffer*>::iterator IterEnd = m_BufferMap.end();

	for(; Iter != IterEnd; ++Iter)
	{
		delete[] Iter->first;
		delete Iter->second;
	}

	m_BufferMap.clear();
}

void CBufferMgr::AddBuffer(TCHAR* _tszBufKey, CBuffer* _pBuffer)
{
	unordered_map<TCHAR*, CBuffer*>::iterator Find_Iter = find_if(m_BufferMap.begin(), m_BufferMap.end(), TStrCompare(_tszBufKey));

	if(Find_Iter != m_BufferMap.end())
	{
		_tprintf(_T("AddBuffer() Error : %s\n"), _tszBufKey);
		Sleep(3000);
		return;
	}

	TCHAR* tszBufKey = new TCHAR[MIN_STR];
	_tcscpy_s(tszBufKey, MIN_STR, _tszBufKey);

	m_BufferMap.insert(unordered_map<TCHAR*, CBuffer*>::value_type(tszBufKey, _pBuffer));
}

void CBufferMgr::RemoveBuffer(TCHAR* _tszBufKey)
{
	unordered_map<TCHAR*, CBuffer*>::iterator Find_Iter = find_if(m_BufferMap.begin(), m_BufferMap.end(), TStrCompare(_tszBufKey));

	if(Find_Iter == m_BufferMap.end())
	{
		_tprintf(_T("RemoveBuffer() Error : %s\n"), _tszBufKey);
		Sleep(3000);
		return;
	}

	delete[] Find_Iter->first;
	delete Find_Iter->second;
	m_BufferMap.erase(Find_Iter);
}

CBuffer* CBufferMgr::GetBuffer(TCHAR* _tszBufKey)
{
	unordered_map<TCHAR*, CBuffer*>::iterator Find_Iter = find_if(m_BufferMap.begin(), m_BufferMap.end(), TStrCompare(_tszBufKey));

	if(Find_Iter == m_BufferMap.end())
	{
		_tprintf(_T("GetBuffer() Error : %s\n"), _tszBufKey);
		Sleep(3000);
		return NULL;
	}

	return Find_Iter->second->Clone();
}