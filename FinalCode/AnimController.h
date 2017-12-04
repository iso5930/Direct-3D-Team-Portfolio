#pragma once

class CAnimController
{
public:
	// Controller
	LPD3DXANIMATIONCONTROLLER m_pAnimController;

	// Animation Cnt
	int m_iAnimCnt;

	// Current Track
	int m_iCurTrack;

	// Next Track
	int m_iNextTrack;

	// Accumulate Time
	double m_dAccTime;

	// Frame Time
	double m_dFrameTime;

public:
	// Clone
	CAnimController* Clone();

	// Get FrameTime
	double GetFrameTime();

	// Get Track Pos
	double GetTrackPos();

	// Set Track Pos
	void SetTrackPos(double _dPos);

	// Set Animation
	void SetAnimation(int _iIndex);

	// Frame Move
	void FrameMove(double _dTime);

public:
	explicit CAnimController();
	~CAnimController();
};