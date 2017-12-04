#include "StdAfx.h"
#include "ExpEnergy.h"

CExpEnergy::CExpEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CEnergyUI(_tszObjKey, _eObjType, NULL)
{
	// TextureVec
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Exp")));

	// Frame
	m_Frame.iStart = 0;
	m_Frame.iCur = 0;
	m_Frame.iEnd = 0;
	m_Frame.fAccTime = 0.0f;
	m_Frame.fFrameTime = 0.0f;

	// ExpMessage
	m_pExpMessage = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.832993f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.719004f, 0.0200093f, 0.0f);
}

CExpEnergy::~CExpEnergy()
{
	Release();
}

void CExpEnergy::Initialize()
{
	CEnergyUI::Initialize();
}

int CExpEnergy::Update()
{
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iCur = ((CPlayer*)pPlayer)->GetStat()->iExp;
		m_iMax = ((CPlayer*)pPlayer)->GetStat()->iMaxExp;
	}

	if(m_dwState & UI_OVER)
	{
		if(m_pExpMessage == NULL)
		{
			m_pExpMessage = new CExpMessage(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(m_pExpMessage, LAYER_TYPE_UI);
			m_pExpMessage->Initialize();
		}
	}
	else
	{
		if(m_pExpMessage != NULL)
		{
			m_pExpMessage->Destroy();
			m_pExpMessage = NULL;
		}
	}

	// SetVB
	m_VertexArr[2].vPos.x = m_VertexArr[3].vPos.x = float(m_iCur) / m_iMax - 0.5f;
	m_VertexArr[2].vTexUV.x = m_VertexArr[3].vTexUV.x = m_VertexArr[2].vPos.x + 0.5f;
	m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);

	CEnergyUI::Update();

	return 0;
}

void CExpEnergy::Render()
{
	CEnergyUI::Render();
}

void CExpEnergy::Release()
{
	// ExpMessage
	if(m_pExpMessage != NULL)
	{
		m_pExpMessage->Destroy();
		m_pExpMessage = NULL;
	}
}