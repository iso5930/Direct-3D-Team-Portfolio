#include "StdAfx.h"
#include "Tristram_BlackSmith_Store.h"

CTristram_BlackSmith_Store::CTristram_BlackSmith_Store(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_BlackSmith_Store"));

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_BLACKSMITH_STORE;
}

CTristram_BlackSmith_Store::~CTristram_BlackSmith_Store()
{
	Release();
}

void CTristram_BlackSmith_Store::Initialize()
{
	CStaticProb::Initialize();
}

int CTristram_BlackSmith_Store::Update()
{
	CStaticProb::Update();

	return 0;
}

void CTristram_BlackSmith_Store::Render()
{
	CStaticProb::Render();
}

void CTristram_BlackSmith_Store::Release()
{
}

void CTristram_BlackSmith_Store::Event()
{
}

void CTristram_BlackSmith_Store::EventEnd()
{
}