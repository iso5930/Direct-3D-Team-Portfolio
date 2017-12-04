#pragma once

class CShader;

class CShaderMgr
{
private:
	unordered_map<TCHAR*, CShader*> m_ShaderMap;

public:
	void AddShader(TCHAR* _tszShaderKey, CShader* _pShader);
	void RemoveShader(TCHAR* _tszShaderKey);
	CShader* GetShader(TCHAR* _tszShaderKey);

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	DECLARE_SINGLETON(CShaderMgr)

private:
	explicit CShaderMgr();
	~CShaderMgr();
};