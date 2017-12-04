#pragma once
#include "effect.h"

class CWizard_ArcaneTorrent_DestoryEffect : public CEffect
{
private:
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_ArcaneTorrent_DestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_ArcaneTorrent_DestoryEffect(void);
};