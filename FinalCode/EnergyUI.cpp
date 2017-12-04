#include "StdAfx.h"
#include "EnergyUI.h"

CEnergyUI::CEnergyUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Cur
	m_iCur = 1;

	// Max
	m_iMax = 1;

	// Vertex
	m_VertexArr[0].vPos.x = -0.5f; m_VertexArr[0].vPos.y = -0.5f; m_VertexArr[0].vPos.z = 0.0f; m_VertexArr[0].vNormal.x = 0.0f; m_VertexArr[0].vNormal.y = 0.0f; m_VertexArr[0].vNormal.z = -1.0f; m_VertexArr[0].vTexUV.x = 0.0f; m_VertexArr[0].vTexUV.y = 1.0f;
	m_VertexArr[1].vPos.x = -0.5f; m_VertexArr[1].vPos.y = 0.5f;  m_VertexArr[1].vPos.z = 0.0f; m_VertexArr[1].vNormal.x = 0.0f; m_VertexArr[1].vNormal.y = 0.0f; m_VertexArr[1].vNormal.z = -1.0f; m_VertexArr[1].vTexUV.x = 0.0f; m_VertexArr[1].vTexUV.y = 0.0f;
	m_VertexArr[2].vPos.x = 0.5f;  m_VertexArr[2].vPos.y = 0.5f;  m_VertexArr[2].vPos.z = 0.0f; m_VertexArr[2].vNormal.x = 0.0f; m_VertexArr[2].vNormal.y = 0.0f; m_VertexArr[2].vNormal.z = -1.0f; m_VertexArr[2].vTexUV.x = 1.0f; m_VertexArr[2].vTexUV.y = 0.0f;
	m_VertexArr[3].vPos.x = 0.5f;  m_VertexArr[3].vPos.y = -0.5f; m_VertexArr[3].vPos.z = 0.0f; m_VertexArr[3].vNormal.x = 0.0f; m_VertexArr[3].vNormal.y = 0.0f; m_VertexArr[3].vNormal.z = -1.0f; m_VertexArr[3].vTexUV.x = 1.0f; m_VertexArr[3].vTexUV.y = 1.0f;

	// Frame
	m_Frame.iStart = 0;
	m_Frame.iCur = 0;
	m_Frame.iEnd = 0;
	m_Frame.fAccTime = 0.0f;
	m_Frame.fFrameTime = 0.0f;

	// BufferCom
	m_pBufferCom = new CBufferCom;
	m_pBufferCom->AddBuffer(_T("Energy"));
	AddComponent(m_pBufferCom);
}

CEnergyUI::~CEnergyUI()
{
	Release();
}

void CEnergyUI::Initialize()
{
	CUI::Initialize();
}

int CEnergyUI::Update()
{	
	// Frame
	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.0f;
		if(++m_Frame.iCur > m_Frame.iEnd)
			m_Frame.iCur = m_Frame.iStart;
			
		m_pBackTexture = m_TextureVec[m_Frame.iCur];
	}

	CUI::Update();

	return 0;
}

void CEnergyUI::Render()
{
	CUI::Render();
}

void CEnergyUI::Release()
{
	// TextureVec
	m_TextureVec.clear();
}