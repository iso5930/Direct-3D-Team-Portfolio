#pragma once

class CShader
{
public:
	LPD3DXEFFECT m_pEffect;
	LPD3DXBUFFER m_pErrBuf;

public:
	explicit CShader(TCHAR* _tszFilePath);
	virtual ~CShader();
};