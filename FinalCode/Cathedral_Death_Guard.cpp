#include "StdAfx.h"
#include "Cathedral_Death_Guard.h"

CCathedral_Death_Guard::CCathedral_Death_Guard(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CStaticProb(_tszObjKey, _eObjType)
{
	// AddBuffer
	m_pBufferCom->AddBuffer(_T("Prob_Cath_Death_Guard"));

	// ProbType
	m_eProbType = PROB_TYPE_CATHEDRAL_DEATH_GAURD;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("죽어가는 가드"));

	// Width
	m_fWidth = 100.0f;

	// Height
	m_fHeight = 50.0f;

	// Depth
	m_fDepth = 100.0f;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(7256.56f, 3.02159f, 2097.35f);
}

CCathedral_Death_Guard::~CCathedral_Death_Guard()
{
	Release();
}

void CCathedral_Death_Guard::Initialize()
{
	CStaticProb::Initialize();
}

int CCathedral_Death_Guard::Update()
{
	CStaticProb::Update();

	return 0;
}

void CCathedral_Death_Guard::Render()
{
	CStaticProb::Render();
}

void CCathedral_Death_Guard::Release()
{
}

void CCathedral_Death_Guard::Event()
{
	// MainQuest10_Message
	CMainQuest10_Message* pMainQuest10_Message = new CMainQuest10_Message(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer->AddObject(pMainQuest10_Message, LAYER_TYPE_UI);
	pMainQuest10_Message->Initialize();
}

void CCathedral_Death_Guard::EventEnd()
{
	// Width & Height & Depth
	m_fWidth = 0.0f; m_fHeight = 0.0f; m_fDepth = 0.0f;
}