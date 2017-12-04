#pragma once

class CScreen : public CBuffer
{
public:
	virtual int Update();
	virtual void Render();
	virtual CScreen* Clone();

public:
	explicit CScreen();
	explicit CScreen(CScreen* _pScreen);
	virtual ~CScreen();
};