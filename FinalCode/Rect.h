#pragma once

class CRect : public CBuffer
{
public:
	virtual int Update();
	virtual void Render();
	virtual CRect* Clone();

public:
	explicit CRect();
	explicit CRect(CRect* _pRect);
	virtual ~CRect();
};