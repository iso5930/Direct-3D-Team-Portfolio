#include "Stdafx.h"
#include "AnimController.h"

CAnimController::CAnimController()
{
	// Controller
	m_pAnimController = NULL;

	// Animation Cnt
	m_iAnimCnt = 0;

	// Current Track
	m_iCurTrack = 0;

	// Next Track
	m_iNextTrack = 1;

	// Accumulate Time
	m_dAccTime = 0.0;

	// Frame Time
	m_dFrameTime = 0.0;
}

CAnimController::~CAnimController()
{
	// Controller
	if(m_pAnimController != NULL)
		m_pAnimController->Release();
}

double CAnimController::GetFrameTime()
{
	return m_dFrameTime;
}

double CAnimController::GetTrackPos()
{
	D3DXTRACK_DESC TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAnimController->GetTrackDesc(m_iCurTrack, &TrackInfo);

	return TrackInfo.Position;
}

void CAnimController::SetTrackPos(double _dPos)
{
	m_pAnimController->SetTrackPosition(m_iCurTrack, _dPos);
}

void CAnimController::SetAnimation(int _iIndex)
{
	if(_iIndex >= m_iAnimCnt)
		return;

	if(m_iCurTrack == 0)
		m_iNextTrack = 1;
	else
		m_iNextTrack = 0;

	// Get AnimationSet
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(_iIndex, &pAnimSet);

	// Get FrameTime
	m_dFrameTime = pAnimSet->GetPeriod();

	// Set Track
	m_pAnimController->SetTrackAnimationSet(m_iNextTrack, pAnimSet);
	pAnimSet->Release();

	// Track Clear
	m_pAnimController->UnkeyAllTrackEvents(m_iCurTrack);
	m_pAnimController->UnkeyAllTrackEvents(m_iNextTrack);

	// Current Disable
	m_pAnimController->KeyTrackEnable(m_iCurTrack, FALSE, m_dAccTime + 0.2);
	m_pAnimController->KeyTrackSpeed(m_iCurTrack, 1.0f, m_dAccTime, 0.2, D3DXTRANSITION_LINEAR);
	m_pAnimController->KeyTrackWeight(m_iCurTrack, 0.1f, m_dAccTime, 0.2, D3DXTRANSITION_LINEAR);

	// Next Enable
	m_pAnimController->SetTrackEnable(m_iNextTrack, TRUE);
	m_pAnimController->KeyTrackSpeed(m_iNextTrack, 1.0f, m_dAccTime, 0.2, D3DXTRANSITION_LINEAR);
	m_pAnimController->KeyTrackWeight(m_iNextTrack, 0.9f, m_dAccTime, 0.2, D3DXTRANSITION_LINEAR);

	// Set
	m_dAccTime = 0.0f;
	m_iCurTrack = m_iNextTrack;
	m_pAnimController->SetTrackPosition(m_iCurTrack, 0.0);
	m_pAnimController->ResetTime();
}

void CAnimController::FrameMove(double _dTime)
{
	m_pAnimController->AdvanceTime(_dTime, NULL);
	m_dAccTime += _dTime;
}

CAnimController* CAnimController::Clone()
{
	CAnimController* pClone = new CAnimController;

	// Controller
	m_pAnimController->CloneAnimationController(m_pAnimController->GetMaxNumAnimationOutputs(),
												m_pAnimController->GetMaxNumAnimationSets(),
												m_pAnimController->GetMaxNumTracks(),
												m_pAnimController->GetMaxNumEvents(),
												&pClone->m_pAnimController);

	// Animation Cnt
	pClone->m_iAnimCnt = m_pAnimController->GetMaxNumAnimationSets();

	// Current Track
	pClone->m_iCurTrack = m_iCurTrack;

	// Next Track
	pClone->m_iNextTrack = m_iNextTrack;

	// Accumulate Time
	pClone->m_dAccTime = m_dAccTime;

	// Frame Time
	pClone->m_dFrameTime = m_dFrameTime;

	return pClone;
}