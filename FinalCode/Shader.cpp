#include "Stdafx.h"
#include "Shader.h"

#include "DeviceMgr.h"

CShader::CShader(TCHAR* _tszFilePath)
{
	if(FAILED(D3DXCreateEffectFromFile(CDeviceMgr::GetInstance()->GetDevice(), _tszFilePath, NULL, NULL, D3DXSHADER_DEBUG, NULL, &m_pEffect, &m_pErrBuf)))
	{
		MessageBoxA(NULL, (char*)m_pErrBuf->GetBufferPointer(), NULL, MB_OK);
		return;
	}
}

CShader::~CShader()
{
	if(m_pEffect != NULL)
		m_pEffect->Release();
	
	if(m_pErrBuf != NULL)
		m_pErrBuf->Release();
}