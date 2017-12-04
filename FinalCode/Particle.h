#pragma once
#include "buffer.h"

class CParticle : public CBuffer
{
public:
	DWORD m_dwOffset;

public:
	virtual int			Update();
	virtual void		Render();
	virtual CParticle*	Clone();

public:
	void RenderParticle(Particle* _pParticle, DWORD _dwVtxCnt, DWORD _dwOffSet);

public:
	explicit CParticle(void);
	explicit CParticle(CParticle* _pParticle);
	virtual ~CParticle(void);
};