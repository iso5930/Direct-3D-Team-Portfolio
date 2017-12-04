#include "StdAfx.h"
#include "Tristram_CampFire.h"

CTristram_CampFire::CTristram_CampFire(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Tristram_CampFire"));

	// ProbType
	m_eProbType = PROB_TYPE_TRISTRAM_CAMPFIRE;
}

CTristram_CampFire::~CTristram_CampFire()
{
	Release();
}

void CTristram_CampFire::Initialize()
{
	CStaticProb::Initialize();
}

int CTristram_CampFire::Update()
{
	CStaticProb::Update();

	return 0;
}

void CTristram_CampFire::Render()
{
	CStaticProb::Render();
}

void CTristram_CampFire::Release()
{
}

void CTristram_CampFire::Event()
{
}

void CTristram_CampFire::EventEnd()
{
}