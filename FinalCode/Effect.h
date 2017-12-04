#pragma once

#include "Object.h"

class CEffect : public CObject
{
public:
	// Owner
	CObject* m_pOwner;

	// Alpha
	float m_fAlpha;

	// Coef
	float m_fCoef; 

	// AttrType
	ATTR_TYPE m_eAttrType;

	// SkillType
	SKILL_TYPE m_eSkillType;

	// Cnt
	int m_iCnt;
	
	// MaxCnt
	int m_iMaxCnt;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetOwner
	CObject* GetOwner() { return m_pOwner; }

	// GetCoef
	float GetCoef() { return m_fCoef; }

	// GetAttrType
	ATTR_TYPE GetAttrType() { return m_eAttrType; }

	// GetSkillType
	SKILL_TYPE GetSkillType() { return m_eSkillType; }

	// SetMaxCnt
	void SetMaxCnt(int _iMaxCnt) { m_iMaxCnt = _iMaxCnt; }

	// AddCnt
	void AddCnt() { ++m_iCnt; }

public:
	explicit CEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CEffect();
};