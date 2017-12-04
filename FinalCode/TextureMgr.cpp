#include "Stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
}

void CTextureMgr::Initialize()
{
}

int CTextureMgr::Update()
{
	return 0;
}

void CTextureMgr::Render()
{
}

void CTextureMgr::Release()
{
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::iterator Iter = m_TextureMap.begin();
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::iterator IterEnd = m_TextureMap.end();

	for(; Iter != IterEnd; ++Iter)
	{
		delete[] Iter->first;
		Iter->second->Release();
	}

	m_TextureMap.clear();
}

void CTextureMgr::AddTexture(TCHAR* _tszTexKey, LPDIRECT3DBASETEXTURE9 _pTexture)
{
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::iterator Find_Iter = find_if(m_TextureMap.begin(), m_TextureMap.end(), TStrCompare(_tszTexKey));

	if(Find_Iter != m_TextureMap.end())
	{
		_tprintf(_T("AddTexture() Error : %s\n"), _tszTexKey);
		Sleep(3000);
		return;
	}

	TCHAR* tszTexKey = new TCHAR[MIN_STR];
	_tcscpy_s(tszTexKey, MIN_STR, _tszTexKey);

	m_TextureMap.insert(unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::value_type(tszTexKey, _pTexture));
}

void CTextureMgr::RemoveTexture(TCHAR* _tszTexKey)
{
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::iterator Find_Iter = find_if(m_TextureMap.begin(), m_TextureMap.end(), TStrCompare(_tszTexKey));

	if(Find_Iter == m_TextureMap.end())
	{
		_tprintf(_T("RemoveTexture() Error : %s\n"), _tszTexKey);
		Sleep(3000);
		return;
	}

	delete[] Find_Iter->first;
	Find_Iter->second->Release();
	m_TextureMap.erase(Find_Iter);
}

LPDIRECT3DBASETEXTURE9 CTextureMgr::GetTexture(TCHAR* _tszTexKey)
{
	unordered_map<TCHAR*, LPDIRECT3DBASETEXTURE9>::iterator Find_Iter = find_if(m_TextureMap.begin(), m_TextureMap.end(), TStrCompare(_tszTexKey));

	if(Find_Iter == m_TextureMap.end())
	{
		_tprintf(_T("GetTexture() Error : %s\n"), _tszTexKey);
		Sleep(3000);
		return NULL;
	}

	return Find_Iter->second;
}