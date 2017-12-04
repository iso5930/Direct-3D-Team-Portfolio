#pragma once
#include "effect.h"

class CBufferCom;
class CWizard_MirrorImage_MirrorImageEffect : public CEffect
{
private:
	CBufferCom* m_pBufferCom;
	float		m_fTime;
	int			m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_MirrorImage_MirrorImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_MirrorImage_MirrorImageEffect(void);
};