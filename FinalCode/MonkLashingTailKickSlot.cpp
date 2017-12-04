#include "StdAfx.h"
#include "MonkLashingTailKickSlot.h"

CMonkLashingTailKickSlot::CMonkLashingTailKickSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_LASHING_TAIL_KICK;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 50.f;

}

CMonkLashingTailKickSlot::~CMonkLashingTailKickSlot()
{
}
SLOT_RESULT CMonkLashingTailKickSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 50 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("공력이 부족합니다."));
		return SLOT_RESULT_EFFORT_EMPTY;
	}

	// Check Pick
	D3DXVECTOR3 vPos;
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPos = pTransformCom->m_vPos;
	}

	// Begin
	CSlot::Begin(_iMode);


	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("TAIL_KICK.ogg"));

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

	// Effort
	m_pOwner->GetStat()->iEffort -= int(50 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	CMonk_LashingTailKick_CreateEfffect* pCreateEffct = new CMonk_LashingTailKick_CreateEfffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 700.f));
	m_pOwner->GetLayer()->AddObject(pCreateEffct, LAYER_TYPE_EFFECT);

	CTransformCom* pTransform = (CTransformCom*)pCreateEffct->GetComponent(COM_TYPE_TRANSFORM);
	pTransform->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 15.f, 0.f);
	pTransform->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pCreateEffct->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkLashingTailKickSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkLashingTailKickSlot::End()
{
	return SLOT_RESULT_NULL;
}
