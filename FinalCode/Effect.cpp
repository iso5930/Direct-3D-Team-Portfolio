#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CObject(_tszObjKey, _eObjType)
{
	// Owner
	m_pOwner = _pOwner;
	
	// Alpha
	m_fAlpha = 0.0f;

	// Coef
	m_fCoef = 1.0f;

	// Attr
	m_eAttrType = ATTR_TYPE_PHYSICAL;

	// SkillType
	m_eSkillType = SKILL_TYPE_END;

	// Cnt
	m_iCnt = 0;

	// MaxCnt
	m_iMaxCnt = 1;
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	CObject::Initialize();
}

int CEffect::Update()
{
	CObject::Update();

	if(m_iCnt >= m_iMaxCnt)
		Destroy();

	return 0;
}

void CEffect::Render()
{
	CObject::Render();
}

void CEffect::Release()
{
}