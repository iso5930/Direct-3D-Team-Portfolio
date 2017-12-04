#include "StdAfx.h"
#include "FollowerEnergy.h"

CFollowerEnergy::CFollowerEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CFollower* _pOwner)
: CEnergyUI(_tszObjKey, _eObjType, NULL)
{
	// TextureVec
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_HPBar")));

	// Frame
	m_Frame.iStart = 0;
	m_Frame.iCur = 0;
	m_Frame.iEnd = 0;
	m_Frame.fAccTime = 0.0f;
	m_Frame.fFrameTime = 0.0f;

	// Owner
	m_pOwner = _pOwner;

	// HPBox
	m_pHPBox = NULL;

	// Portrait
	m_pPortrait = NULL;

	// MenuMessage
	m_pMenuMessage = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.783992f, 0.750995f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0879998f, 0.018998f, 0.0f);
}

CFollowerEnergy::~CFollowerEnergy()
{
	Release();
}

void CFollowerEnergy::Initialize()
{
	CEnergyUI::Initialize();

	// HPBox
	m_pHPBox = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_HPBox"));
	m_pLayer->AddObject(m_pHPBox, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)m_pHPBox->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.783992f, 0.750995f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0949997f, 0.0269997f, 0.0f);

	m_pHPBox->Initialize();

	// Portrait
	if(m_pOwner->GetFollowerInfo()->eFollowerType == FOLLOWER_TYPE_ENCHANTRESS)
		m_pPortrait = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Enchantress"));

	m_pLayer->AddObject(m_pPortrait, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortrait->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.782992f, 0.836994f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0949997f, 0.153f, 0.0f);

	m_pPortrait->Initialize();
}

int CFollowerEnergy::Update()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.831491f, 0.760494f), &D3DXVECTOR2(-0.736492f, 0.913494f)))
	{
		// FollowerWindow
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);

			if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER) == NULL)
			{
				CFollowerWindow* pFollowerWindow = new CFollowerWindow(_T("FollowerWindow"), OBJ_TYPE_STATIC);
				m_pLayer->AddObject(pFollowerWindow, LAYER_TYPE_UI);
				pFollowerWindow->Initialize();
			}
		}
		// Disemploy
		else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
		{
			CInputMgr::GetInstance()->MouseStop(DIM_RBUTTON);
			CItemMgr::GetInstance()->ResetFollowerEquip();

			m_pOwner->Destroy();
			Destroy();
		}

		if(m_pMenuMessage == NULL)
		{
			m_pMenuMessage = new CFollowerMenuMessage(NULL, OBJ_TYPE_STATIC, m_pOwner);
			m_pLayer->AddObject(m_pMenuMessage, LAYER_TYPE_UI);
			m_pMenuMessage->Initialize();
		}
	}
	else
	{
		if(m_pMenuMessage != NULL)
		{
			m_pMenuMessage->Destroy();
			m_pMenuMessage = NULL;
		}
	}

	m_iCur = m_pOwner->GetFollowerInfo()->stat.iLife;
	m_iMax = m_pOwner->GetFollowerInfo()->stat.iMaxLife + m_pOwner->GetFollowerInfo()->stat.iVitality * 10;

	// SetVB
	m_VertexArr[2].vPos.x = m_VertexArr[3].vPos.x = float(m_iCur) / m_iMax - 0.5f;
	m_VertexArr[2].vTexUV.x = m_VertexArr[3].vTexUV.x = m_VertexArr[2].vPos.x + 0.5f;
	m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);

	CEnergyUI::Update();

	return 0;
}

void CFollowerEnergy::Render()
{
	CEnergyUI::Render();
	
	TCHAR tszText[MIN_STR];
	if(m_pOwner->GetFollowerInfo()->eFollowerType == FOLLOWER_TYPE_ENCHANTRESS)
		StringCbPrintf(tszText, sizeof(tszText), _T("Lv.%d %s"), m_pOwner->GetFollowerInfo()->stat.iLevel, _T("¿ä¼ú»ç"));
	
	RECT rcText;
	SetRect(&rcText, 39, 15, 239, 27);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CFollowerEnergy::Release()
{
	// HPBox
	if(m_pHPBox != NULL)
	{
		m_pHPBox->Destroy();
		m_pHPBox = NULL;
	}

	// Portrait
	if(m_pPortrait != NULL)
	{
		m_pPortrait->Destroy();
		m_pPortrait = NULL;
	}

	// Menu
	if(m_pMenuMessage != NULL)
	{
		m_pMenuMessage->Destroy();
		m_pMenuMessage = NULL;
	}
}

void CFollowerEnergy::Enable()
{
	AddComponent(new CRenderCom(RENDER_TYPE_UI));
	m_pHPBox->AddComponent(new CRenderCom(RENDER_TYPE_UI));
	m_pPortrait->AddComponent(new CRenderCom(RENDER_TYPE_UI));
	if(m_pMenuMessage != NULL) { m_pMenuMessage->AddComponent(new CRenderCom(RENDER_TYPE_UI)); }
}

void CFollowerEnergy::Disable()
{
	RemoveComponent(COM_TYPE_RENDER);
	m_pHPBox->RemoveComponent(COM_TYPE_RENDER);
	m_pPortrait->RemoveComponent(COM_TYPE_RENDER);
	if(m_pMenuMessage != NULL) { m_pMenuMessage->RemoveComponent(COM_TYPE_RENDER); }
}