#include "Stdafx.h"
#include "BufferCom.h"

CBufferCom::CBufferCom()
{
	// ComType
	m_eComType = COM_TYPE_BUFFER;
}

CBufferCom::~CBufferCom()
{
	Release();
}

void CBufferCom::Initialize()
{
}

int CBufferCom::Update()
{
	for(size_t i = 0; i < m_BufferVec.size(); ++i)
		m_BufferVec[i]->Update();

	return 0;
}

void CBufferCom::Render()
{
	for(size_t i = 0; i < m_BufferVec.size(); ++i)
		m_BufferVec[i]->Render();
}

void CBufferCom::Release()
{
	for(size_t i = 0; i < m_BufferVec.size(); ++i)
		delete m_BufferVec[i];
	m_BufferVec.clear();
}

void CBufferCom::AddBuffer(TCHAR* _tszBufKey)
{
	m_BufferVec.push_back(CBufferMgr::GetInstance()->GetBuffer(_tszBufKey));
}