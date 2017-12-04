#include "StdAfx.h"
#include "MonkMantraOfConvictionSlot.h"

CMonkMantraOfConvictionSlot::CMonkMantraOfConvictionSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_MANTRAS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_MANTRA_OF_CONVICTION;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkMantraOfConvictionSlot::~CMonkMantraOfConvictionSlot()
{
}

SLOT_RESULT CMonkMantraOfConvictionSlot::Begin(int _iMode)
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

	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("MANTRA.ogg"));

	// Effort
	m_pOwner->GetStat()->iEffort -= int(50 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_MONK_MANTRA , 3600.f));

	vector<CObject*> vecFindObject;
	m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Mantra"), LAYER_TYPE_EFFECT);

	if(vecFindObject.size() != 0)
	{
		for(size_t i = 0; i < vecFindObject.size(); ++i)
		{
			vecFindObject[i]->Destroy();
		}
	}

	CMonk_MantraOfConviction_DecalEffect* pDecal = new CMonk_MantraOfConviction_DecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecal, LAYER_TYPE_EFFECT);
	pDecal->Initialize();

	for(int i = 0; i < 18; ++i)
	{
		float fAngle = D3DXToRadian(20.f) * (float)i;
		D3DXVECTOR3 vDir(1.f, 0.f, 0.f);
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, fAngle);
		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

		int iSizeY = (rand() % 30) + 20;

		CMonk_MantraOfConviction_CastingEffect* pCastingEffect = new CMonk_MantraOfConviction_CastingEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pCastingEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pCastingEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = (m_pTransformCom->m_vPos + vDir * 40.f) + D3DXVECTOR3(0.f, float(iSizeY / 2.f), 0.f);
		pTransformCom->m_vAngle.y = fAngle - D3DXToRadian(90.f);
		pTransformCom->m_vSize.y = float(iSizeY);
		pCastingEffect->Initialize();
	}
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfConvictionSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfConvictionSlot::End()
{
	return SLOT_RESULT_NULL;
}
