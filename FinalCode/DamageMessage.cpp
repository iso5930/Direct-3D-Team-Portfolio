#include "StdAfx.h"
#include "DamageMessage.h"

CDamageMessage::CDamageMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iDamage, D3DXCOLOR* _pColor)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Alpha"))
{
	// Damage
	_itot_s(_iDamage, m_tszText, 10);

	// Calc
	RECT rcCalc;
	CFontMgr::GetInstance()->GetBauhaus(16, 7)->DrawText(NULL, m_tszText, -1, &rcCalc, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Width
	m_iWidth = rcCalc.right - rcCalc.left;

	// Height
	m_iHeight = rcCalc.bottom - rcCalc.top;
	
	// Time
	m_fTime = 0.0f;

	// Color
	m_dwColor = *_pColor;

	// Velo
	m_vVelo.x = (rand() % 1000 - 500) / 1000.0f;
	m_vVelo.y = 0.2f;

	// Move
	m_vMove = D3DXVECTOR2(0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CDamageMessage::~CDamageMessage()
{
	Release();
}

void CDamageMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CDamageMessage::Update()
{
	CMessageUI::Update();

	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
		Destroy();

	// Alpha
	m_dwColor.a = 1.0f - (m_fTime / 1.0f);
	if(m_dwColor.a < 0.0f)
		m_dwColor.a = 0.0f;

	// Velo
	m_vVelo.y = 0.2f - m_fTime;

	// Move
	m_vMove.x += m_vVelo.x * 2.0f * m_fTime;
	m_vMove.y += m_vVelo.y * 100.0f * CTimeMgr::GetInstance()->GetDeltaTime();

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetViewProj());

	return 0;
}

void CDamageMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vProjPos(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&vProjPos, &vProjPos, &m_pTransformCom->m_mWorld);

	D3DXVECTOR3 vScreenPos;
	ProjToScreen(&vScreenPos, &vProjPos);

	RECT rcText;
	SetRect(&rcText, long(vScreenPos.x - m_iWidth / 2.0f + m_vMove.x), long(vScreenPos.y - m_iHeight / 2.0f - m_vMove.y), long(vScreenPos.x + m_iWidth / 2.0f + m_vMove.x), long(vScreenPos.y + m_iHeight / 2.0f - m_vMove.y));
	CFontMgr::GetInstance()->GetBauhaus(16, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, m_dwColor);
}

void CDamageMessage::Release()
{
}