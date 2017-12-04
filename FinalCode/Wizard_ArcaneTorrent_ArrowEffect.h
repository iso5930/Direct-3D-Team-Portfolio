#pragma once
#include "effect.h"

class CWizard_ArcaneTorrent_TrailEffect;
class CWizard_ArcaneTorrent_ArrowTrailEffect;
class CWizard_ArcaneTorrent_ArrowEffect : public CEffect
{
private:
	float		m_fDetail;
	D3DXVECTOR3 m_vBezierPos;	
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vEndPos;

	CWizard_ArcaneTorrent_TrailEffect* m_pTrailEffect;
	CWizard_ArcaneTorrent_ArrowTrailEffect* m_pArrowTrailEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_ArcaneTorrent_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vDestPos);
	virtual ~CWizard_ArcaneTorrent_ArrowEffect(void);
};