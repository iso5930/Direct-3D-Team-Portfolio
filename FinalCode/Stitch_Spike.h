#pragma once
#include "effect.h"

class CStitch_Spike :
	public CEffect
{
private:
	float m_fTime;
	Bone* m_pBone;
	int m_iScaleMode;	// 0 : ũ��, 1: �۰�, 2: �Ҹ�

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CStitch_Spike(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, Bone* _pBone);
	virtual ~CStitch_Spike(void);
};
