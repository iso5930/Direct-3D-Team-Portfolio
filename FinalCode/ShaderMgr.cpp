#include "Stdafx.h"
#include "ShaderMgr.h"

#include "Shader.h"

IMPLEMENT_SINGLETON(CShaderMgr)

CShaderMgr::CShaderMgr()
{
}

CShaderMgr::~CShaderMgr()
{
	Release();
}

void CShaderMgr::Initialize()
{
}

int CShaderMgr::Update()
{
	return 0;
}

void CShaderMgr::Render()
{
}

void CShaderMgr::Release()
{
	unordered_map<TCHAR*, CShader*>::iterator Shader_Iter = m_ShaderMap.begin();
	unordered_map<TCHAR*, CShader*>::iterator Shader_IterEnd = m_ShaderMap.end();

	for(; Shader_Iter != Shader_IterEnd; ++Shader_Iter)
	{
		delete[] Shader_Iter->first;
		delete Shader_Iter->second;
	}

	m_ShaderMap.clear();
}

void CShaderMgr::AddShader(TCHAR* _tszShaderKey, CShader* _pShader)
{
	unordered_map<TCHAR*, CShader*>::iterator Find_Iter = find_if(m_ShaderMap.begin(), m_ShaderMap.end(), TStrCompare(_tszShaderKey));

	if(Find_Iter != m_ShaderMap.end())
		return;

	TCHAR* tszShaderKey = new TCHAR[MIN_STR];
	_tcscpy_s(tszShaderKey, MIN_STR, _tszShaderKey);

	m_ShaderMap.insert(unordered_map<TCHAR*, CShader*>::value_type(tszShaderKey, _pShader));
}

void CShaderMgr::RemoveShader(TCHAR* _tszShaderKey)
{
	unordered_map<TCHAR*, CShader*>::iterator Find_Iter = find_if(m_ShaderMap.begin(), m_ShaderMap.end(), TStrCompare(_tszShaderKey));

	if(Find_Iter == m_ShaderMap.end())
		return;

	delete[] Find_Iter->first;
	delete Find_Iter->second;
	m_ShaderMap.erase(Find_Iter);
}

CShader* CShaderMgr::GetShader(TCHAR* _tszShaderKey)
{
	unordered_map<TCHAR*, CShader*>::iterator Find_Iter = find_if(m_ShaderMap.begin(), m_ShaderMap.end(), TStrCompare(_tszShaderKey));

	if(Find_Iter == m_ShaderMap.end())
		return NULL;

	return Find_Iter->second;
}