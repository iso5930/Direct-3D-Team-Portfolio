#pragma once

class CCube : public CBuffer
{
public:
	virtual int Update();
	virtual void Render();
	virtual CCube* Clone();

public:
	explicit CCube();
	explicit CCube(CCube* _pCube);
	virtual ~CCube();
};