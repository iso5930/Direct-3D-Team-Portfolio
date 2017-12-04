#include "StdAfx.h"
#include "EffortEnergy.h"

CEffortEnergy::CEffortEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CEnergyUI(_tszObjKey, _eObjType, NULL)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort00")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort01")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort02")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort03")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort04")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort05")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort06")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort07")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort08")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort09")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort10")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort11")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort12")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort13")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort14")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort15")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort16")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort17")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort18")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort19")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort20")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort21")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort22")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort23")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort24")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort25")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort26")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort27")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort28")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort29")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort30")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort31")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort32")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort33")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort34")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort35")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort36")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort37")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort38")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort39")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort40")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort41")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort42")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort43")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort44")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort45")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort46")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort47")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort48")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort49")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort50")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort51")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort52")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort53")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort54")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort55")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort56")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort57")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort58")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Effort59")));

	// Frame
	m_Frame.iStart = 0;
	m_Frame.iCur = 0;
	m_Frame.iEnd = 59;
	m_Frame.fAccTime = 0.0f;
	m_Frame.fFrameTime = 0.1f;

	// EffortMessage
	m_pEffortMessage = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.44f, -0.835f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.154f, 0.272f, 0.0f);
}

CEffortEnergy::~CEffortEnergy()
{
	Release();
}

void CEffortEnergy::Initialize()
{
	CEnergyUI::Initialize();
}

int CEffortEnergy::Update()
{
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iCur = ((CPlayer*)pPlayer)->GetStat()->iEffort;
		m_iMax = ((CPlayer*)pPlayer)->GetStat()->iMaxEffort;
	}

	if(m_dwState & UI_OVER)
	{
		if(m_pEffortMessage == NULL)
		{
			m_pEffortMessage = new CEffortMessage(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(m_pEffortMessage, LAYER_TYPE_UI);
			m_pEffortMessage->Initialize();
		}
	}
	else
	{
		if(m_pEffortMessage != NULL)
		{
			m_pEffortMessage->Destroy();
			m_pEffortMessage = NULL;
		}
	}

	// SetVB
	m_VertexArr[1].vPos.y = m_VertexArr[2].vPos.y = float(m_iCur) / m_iMax - 0.5f;
	m_VertexArr[1].vTexUV.y = m_VertexArr[2].vTexUV.y = -m_VertexArr[1].vPos.y + 0.5f;
	m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);

	CEnergyUI::Update();

	return 0;
}

void CEffortEnergy::Render()
{
	CEnergyUI::Render();
}

void CEffortEnergy::Release()
{
	// EffortMessage
	if(m_pEffortMessage != NULL)
	{
		m_pEffortMessage->Destroy();
		m_pEffortMessage = NULL;
	}
}