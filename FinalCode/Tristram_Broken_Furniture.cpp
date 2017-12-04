#include "StdAfx.h"
#include "Tristram_Broken_Furniture.h"

CTristram_Broken_Furniture::CTristram_Broken_Furniture(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_Broken_Furniture"));

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_BROKEN_FURNITURE;
}

CTristram_Broken_Furniture::~CTristram_Broken_Furniture()
{
	Release();
}

void CTristram_Broken_Furniture::Initialize()
{
	CStaticProb::Initialize();
}

int CTristram_Broken_Furniture::Update()
{
	CStaticProb::Update();

	return 0;
}

void CTristram_Broken_Furniture::Render()
{
	CStaticProb::Render();
}

void CTristram_Broken_Furniture::Release()
{
}

void CTristram_Broken_Furniture::Event()
{
}

void CTristram_Broken_Furniture::EventEnd()
{
}