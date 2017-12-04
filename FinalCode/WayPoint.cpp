#include "Stdafx.h"
#include "WayPoint.h"

CWayPoint::CWayPoint()
{
	// Cell
	m_pCell = NULL;

	// Point
	ZeroMemory(&m_vPoint, sizeof(D3DXVECTOR3));
}

CWayPoint::~CWayPoint()
{
}