#include "StdAfx.h"
#include "DemonHunterSmokeScreenSlot.h"

CDemonHunterSmokeScreenSlot::CDemonHunterSmokeScreenSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_SMOKE_SCREEN;

	// ColldownTime
	m_fCooldownTime = 3.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterSmokeScreenSlot::~CDemonHunterSmokeScreenSlot()
{
}

SLOT_RESULT CDemonHunterSmokeScreenSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Control
	if(m_pOwner->GetStat()->iControl < 12 * (1.0f - m_pOwner->GetReducedControlConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("절제가 부족합니다."));
		return SLOT_RESULT_CONTROL_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SMOKE_SCREEN.ogg"));


	// Control
	m_pOwner->GetStat()->iControl -= int(12 * (1.0f - m_pOwner->GetReducedControlConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_SHADOW_POWER , 5.f));

	CDemonHunter_SmokeScreen_DecalEffect* pDecalEffect = new CDemonHunter_SmokeScreen_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalEffect->Initialize();

	for(int i = 0; i < 25; ++i)
	{
		int iRand = rand() % 360;

		D3DXVECTOR3 vDir(0.f, 0.f, 1.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(iRand));
		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

		D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + vDir * 50.f; 
		D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + vDir * 130.f;
		vDestPos.y += 300.f;

		vDir = vDestPos - vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		CDemonHunter_SmokeScreen_FlashEffect* pFlashEffect = new CDemonHunter_SmokeScreen_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &D3DXVECTOR3(0.f, 0.f, 0.f));
		m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos + D3DXVECTOR3(0.f, 5.f, 0.f);
		pTransformCom->m_vAngle.y = D3DXToRadian(iRand);
		pFlashEffect->Initialize();
	}

	CDemonHunter_SmokeScreen_SmokeCreateEffect* pCreateEffect = new CDemonHunter_SmokeScreen_SmokeCreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
	pCreateEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSmokeScreenSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSmokeScreenSlot::End()
{
	return SLOT_RESULT_NULL;
}
