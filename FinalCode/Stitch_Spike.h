#pragma once
#include "effect.h"

class CStitch_Spike :
	public CEffect
{
private:
	float m_fTime;
	Bone* m_pBone;
	int m_iScaleMode;	// 0 : 크게, 1: 작게, 2: 소멸

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CStitch_Spike(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, Bone* _pBone);
	virtual ~CStitch_Spike(void);
};
