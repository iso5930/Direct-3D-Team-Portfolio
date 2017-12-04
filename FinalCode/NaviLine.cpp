#include "Stdafx.h"
#include "NaviLine.h"

CNaviLine::CNaviLine()
{
	// Src
	ZeroMemory(&m_vSrc, sizeof(D3DXVECTOR3));

	// Dst
	ZeroMemory(&m_vDst, sizeof(D3DXVECTOR3));

	// Mid
	ZeroMemory(&m_vMid, sizeof(D3DXVECTOR3));

	// Dir
	ZeroMemory(&m_vDir, sizeof(D3DXVECTOR3));

	// Normal
	ZeroMemory(&m_vNormal, sizeof(D3DXVECTOR3));

	// Size
	m_fSize = 0.0f;
}

CNaviLine::~CNaviLine()
{
}

void CNaviLine::Setup(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst)
{
	// Src
	m_vSrc = (*_pSrc);
	m_vSrc.y = 0.0f;

	// Dst
	m_vDst = (*_pDst);
	m_vDst.y = 0.0f;

	// Mid
	m_vMid = (*_pSrc + *_pDst) / 2.0f;

	// Dir
	m_vDir = m_vDst - m_vSrc;

	// Size
	m_fSize = D3DXVec3Length(&m_vDir);

	// Normal
	m_vNormal.z = -m_vDir.x;
	m_vNormal.x = m_vDir.z;

	// Normalize
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	D3DXVec3Normalize(&m_vNormal, &m_vNormal);
}

POINT_CLASS CNaviLine::Classify(D3DXVECTOR3* _pPoint)
{
	D3DXVECTOR3 v = (*_pPoint) - m_vSrc;
	v.y = 0.0f;

	if(D3DXVec3Dot(&v, &m_vNormal) > MIN_EPSILON)
		return POINT_CLASS_RIGHT_SIDE;
	else if(D3DXVec3Dot(&v, &m_vNormal) < MIN_EPSILON)
		return POINT_CLASS_LEFT_SIDE;

	return POINT_CLASS_ON_LINE;
}

LINE_CLASS CNaviLine::Classify(CNaviLine* _pLine, D3DXVECTOR3* _pIntersectPoint /*= NULL*/)
{
	float Az_Cz = m_vSrc.z - _pLine->m_vSrc.z;
	float Dx_Cx = _pLine->m_vDst.x - _pLine->m_vSrc.x;
	float Ax_Cx = m_vSrc.x - _pLine->m_vSrc.x;
	float Dz_Cz = _pLine->m_vDst.z - _pLine->m_vSrc.z;
	float Bx_Ax = m_vDst.x - m_vSrc.x;
	float Bz_Az = m_vDst.z - m_vSrc.z;

	float Numerator = (Az_Cz * Dx_Cx) - (Ax_Cx * Dz_Cz);
	float Denominator = (Bx_Ax * Dz_Cz) - (Bz_Az * Dx_Cx);

	if(!Denominator)
	{
		if(!Numerator)
			return LINE_CLASS_COLLINEAR;

		return LINE_CLASS_PARALLEL;
	}

	float FactorAB = Numerator / Denominator;
	float FactorCD = ((Az_Cz * Bx_Ax) - (Ax_Cx * Bz_Az)) / Denominator;

	if (fabs(FactorCD) < 1.0e-6f)
		FactorCD = 1.0e-6f;
	if (fabs(FactorCD - 1.0f) < 1.0e-6f)
		FactorCD = 1.0f - 1.0e-6f;

	if(_pIntersectPoint)
	{
		_pIntersectPoint->x = (m_vSrc.x + (FactorAB * Bx_Ax));
		_pIntersectPoint->y = 0.0f;
		_pIntersectPoint->z = (m_vSrc.z + (FactorAB * Bz_Az));
	}

	if((FactorAB >= 0.0f) && (FactorAB <= 1.0f) && (FactorCD >= 0.0f) && (FactorCD <= 1.0f))
		return LINE_CLASS_SEGMENT;
	else if((FactorCD >= 0.0f) && (FactorCD <= 1.0f))
		return LINE_CLASS_A_BISECT_B;
	else if((FactorAB >= 0.0f) && (FactorAB <= 1.0f))
		return LINE_CLASS_B_BISECT_A;

	return LINE_CLASS_INTERSECT;
}