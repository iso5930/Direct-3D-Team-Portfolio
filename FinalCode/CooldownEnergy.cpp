#include "StdAfx.h"
#include "CooldownEnergy.h"

CCooldownEnergy::CCooldownEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CSlot* _pSlot)
: CEnergyUI(_tszObjKey, _eObjType, NULL)
{
	// TextureVec
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Energy_Cooldown")));

	// Frame
	m_Frame.iStart = 0;
	m_Frame.iCur = 0;
	m_Frame.iEnd = 0;
	m_Frame.fAccTime = 0.0f;
	m_Frame.fFrameTime = 0.0f;

	// Slot
	m_pSlot = _pSlot;
}

CCooldownEnergy::~CCooldownEnergy()
{
	Release();
}

void CCooldownEnergy::Initialize()
{
	CEnergyUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF9;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000006;
}

int CCooldownEnergy::Update()
{
	if(m_pSlot->GetMaxCharge() == 0)
	{
		float fCoef = m_pSlot->GetTime() / m_pSlot->GetCooldownTime();
		if(fCoef > 1.0f)
			fCoef = 1.0f;

		// SetVB
		m_VertexArr[1].vPos.y = m_VertexArr[2].vPos.y = 0.5f - fCoef;
		m_VertexArr[1].vTexUV.y = m_VertexArr[2].vTexUV.y = -m_VertexArr[1].vPos.y + 0.5f;
		m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);
	}
	else
	{
		if(m_pSlot->GetCharge() > 0)
		{
			// SetVB
			m_VertexArr[1].vPos.y = m_VertexArr[2].vPos.y = -0.5f;
			m_VertexArr[1].vTexUV.y = m_VertexArr[2].vTexUV.y = 1.0f;
			m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);
		}
		else
		{
			float fCoef = m_pSlot->GetChargingTime() / m_pSlot->GetChargeTime();
			if(fCoef > 1.0f)
				fCoef = 1.0f;

			// SetVB
			m_VertexArr[1].vPos.y = m_VertexArr[2].vPos.y = 0.5f - fCoef;
			m_VertexArr[1].vTexUV.y = m_VertexArr[2].vTexUV.y = -m_VertexArr[1].vPos.y + 0.5f;
			m_pBufferCom->m_BufferVec[0]->SetVB(m_VertexArr, 4);
		}
	}

	CEnergyUI::Update();

	return 0;
}

void CCooldownEnergy::Render()
{
	CEnergyUI::Render();

	if(m_pSlot->GetMaxCharge() != 0)
	{
		TCHAR tszCharge[MIN_STR];
		_itot_s(m_pSlot->GetCharge(), tszCharge, 10);

		D3DXVECTOR3 vPos;
		ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

		RECT rcText;
		SetRect(&rcText, long(vPos.x - 35.0f), long(vPos.y + 5.0f), long(vPos.x + 15.0f), long(vPos.y + 17.0f));

		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszCharge, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CCooldownEnergy::Release()
{
}