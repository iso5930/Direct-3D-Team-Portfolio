#include "StdAfx.h"
#include "MonsterEnergy.h"

CMonsterEnergy::CMonsterEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CMonster* _pOwner)
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

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.877993f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.208f, 0.042998f, 0.0f);
}

CMonsterEnergy::~CMonsterEnergy()
{
	Release();
}

void CMonsterEnergy::Initialize()
{
	CEnergyUI::Initialize();

	// HPBox
	m_pHPBox = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_HPBox"));
	m_pLayer->AddObject(m_pHPBox, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)m_pHPBox->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.876993f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.219f, 0.0529997f, 0.0f);

	m_pHPBox->Initialize();
}

int CMonsterEnergy::Update()
{
	if(m_pOwner->IsOver() == false)
		Destroy();

	m_iCur = m_pOwner->GetStat()->iLife;
	m_iMax = m_pOwner->GetStat()->iMaxLife;

	// SetVB
	m_VertexArr[2].vPos.x = m_VertexArr[3].vPos.x = float(m_iCur) / m_iMax - 0.5f;
	m_VertexArr[2].vTexUV.x = m_VertexArr[3].vTexUV.x = m_VertexArr[2].vPos.x + 0.5f;
	m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);

	CEnergyUI::Update();

	return 0;
}

void CMonsterEnergy::Render()
{
	CEnergyUI::Render();

	RECT rcText;
	SetRect(&rcText, 0, 15, WINCX, 29);
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, m_pOwner->GetInfo()->tszName, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CMonsterEnergy::Release()
{
	// HPBox
	if(m_pHPBox != NULL)
	{
		m_pHPBox->Destroy();
		m_pHPBox = NULL;
	}
}