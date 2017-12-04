#pragma once

#include "Buffer.h"

class CTrail : public CBuffer
{
public:
	virtual int Update();
	virtual void Render();
	virtual CTrail* Clone();

public:
	// SetVB
	virtual void SetVB(Vertex* _pVS, DWORD _dwVtxCnt);

public:
	explicit CTrail();
	explicit CTrail(CTrail* _pTrail);
	virtual ~CTrail();
};
