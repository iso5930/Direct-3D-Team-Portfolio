#pragma once

#include "Component.h"

class CBuffer;

class CBufferCom : public CComponent
{
public:
	vector<CBuffer*> m_BufferVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void AddBuffer(TCHAR* _tszBufKey);

public:
	explicit CBufferCom();
	virtual ~CBufferCom();
};