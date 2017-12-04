#pragma once

class CEnergy : public CBuffer
{
public:
	virtual int Update();
	virtual void Render();
	virtual CEnergy* Clone();

public:
	explicit CEnergy();
	virtual ~CEnergy();
};