#pragma once

inline bool Equals(float lhs, float rhs, float eps)
{
	return fabs(lhs - rhs) < eps ? true : false;
}

inline void GetBezier(D3DXVECTOR3* _pOut, D3DXVECTOR3* _pV1, D3DXVECTOR3* _pV2, D3DXVECTOR3* _pV3, float _fDetail)
{
	ZeroMemory(_pOut, sizeof(D3DXVECTOR3));
	_pOut->x = _pV3->x * (_fDetail * _fDetail) + _pV2->x * (2.0f * _fDetail * (1.0f - _fDetail)) + _pV1->x * ((1.0f - _fDetail) * (1.0f - _fDetail));
	_pOut->y = _pV3->y * (_fDetail * _fDetail) + _pV2->y * (2.0f * _fDetail * (1.0f - _fDetail)) + _pV1->y * ((1.0f - _fDetail) * (1.0f - _fDetail));
	_pOut->z = _pV3->z * (_fDetail * _fDetail) + _pV2->z * (2.0f * _fDetail * (1.0f - _fDetail)) + _pV1->z * ((1.0f - _fDetail) * (1.0f - _fDetail));
}

inline float RevisionDot(float _fDot)
{
	if(_fDot >= 1.0f)
		_fDot = 0.999999f;
	else if(_fDot <= -1.0f)
		_fDot = -0.999999f;

	return _fDot;
}

inline void ScreenToProj(D3DXVECTOR3* _pOut, D3DXVECTOR3* _pIn)
{
	_pOut->x = _pIn->x / (WINCX * 0.5f) - 1.0f;
	_pOut->y = (WINCY - _pIn->y) / (WINCY * 0.5f) - 1.0f;
}

inline void ScreenToProj(D3DXVECTOR2* _pOut, D3DXVECTOR2* _pIn)
{
	_pOut->x = _pIn->x / (WINCX * 0.5f) - 1.0f;
	_pOut->y = (WINCY - _pIn->y) / (WINCY * 0.5f) - 1.0f;
}

inline void ProjToScreen(D3DXVECTOR3* _pOut, D3DXVECTOR3* _pIn)
{
	_pOut->x = (_pIn->x + 1.0f) * (WINCX * 0.5f);
	_pOut->y = WINCY - (_pIn->y + 1.0f) * (WINCY * 0.5f);
}

inline void ScreenToWorld(Ray* _pOut, D3DXVECTOR3* _pIn, D3DXMATRIX* _pProj, D3DXMATRIX* _pInvView)
{
	D3DXVECTOR3 v;
	v.x =  ( ( ( 2.0f * _pIn->x ) / float(WINCX)  ) - 1 ) / _pProj->_11;
	v.y = -( ( ( 2.0f * _pIn->y ) / float(WINCY)  ) - 1 ) / _pProj->_22;
	v.z =  1.0f;

	_pOut->vDir.x  = v.x*_pInvView->_11 + v.y*_pInvView->_21 + v.z*_pInvView->_31;
	_pOut->vDir.y  = v.x*_pInvView->_12 + v.y*_pInvView->_22 + v.z*_pInvView->_32;
	_pOut->vDir.z  = v.x*_pInvView->_13 + v.y*_pInvView->_23 + v.z*_pInvView->_33;
	_pOut->vSrc.x = _pInvView->_41;
	_pOut->vSrc.y = _pInvView->_42;
	_pOut->vSrc.z = _pInvView->_43;
}

inline void MatrixToPos(D3DXVECTOR3* _pV, D3DXMATRIX* _pM)
{
	memcpy_s(_pV, sizeof(D3DXVECTOR3), &_pM->_41, sizeof(D3DXVECTOR3));
}

inline void MatrixToAxisX(D3DXVECTOR3* _pV, D3DXMATRIX* _pM)
{
	memcpy_s(_pV, sizeof(D3DXVECTOR3), &_pM->_11, sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(_pV, _pV);
}

inline void MatrixToAxisY(D3DXVECTOR3* _pV, D3DXMATRIX* _pM)
{
	memcpy_s(_pV, sizeof(D3DXVECTOR3), &_pM->_21, sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(_pV, _pV);
}

inline void MatrixToAxisZ(D3DXVECTOR3* _pV, D3DXMATRIX* _pM)
{
	memcpy_s(_pV, sizeof(D3DXVECTOR3), &_pM->_31, sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(_pV, _pV);
}

inline void MatrixRotation(D3DXMATRIX *pOUT, FLOAT rx, FLOAT ry, FLOAT rz)
{
	D3DXMATRIX mRotate;
	D3DXMatrixIdentity(pOUT);

	D3DXMatrixRotationZ(&mRotate, rz);
	(*pOUT) *= mRotate;

	D3DXMatrixRotationX(&mRotate, rx);
	(*pOUT) *= mRotate;

	D3DXMatrixRotationY(&mRotate, ry);
	(*pOUT) *= mRotate;
}

inline void MatrixLookAtLH(D3DXMATRIX *pOut, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRight, D3DXVECTOR3 *pUp, D3DXVECTOR3 *pLook)
{
	D3DXVec3Normalize(pRight, pRight);

	D3DXVec3Cross(pUp, pLook, pRight);
	D3DXVec3Normalize(pUp, pUp);

	D3DXVec3Cross(pRight, pUp, pLook);
	D3DXVec3Normalize(pRight, pRight);

	float x = -D3DXVec3Dot(pRight, pPos);
	float y = -D3DXVec3Dot(pUp, pPos);
	float z = -D3DXVec3Dot(pLook, pPos);

	pOut->m[0][0] = pRight->x;	pOut->m[0][1] = pUp->x;		pOut->m[0][2] = pLook->x;	pOut->m[0][3] = 0.0f;
	pOut->m[1][0] = pRight->y;	pOut->m[1][1] = pUp->y;		pOut->m[1][2] = pLook->y;	pOut->m[1][3] = 0.0f;
	pOut->m[2][0] = pRight->z;	pOut->m[2][1] = pUp->z;		pOut->m[2][2] = pLook->z;	pOut->m[2][3] = 0.0f;
	pOut->m[3][0] = x;			pOut->m[3][1] = y;			pOut->m[3][2] = z;			pOut->m[3][3] = 1.0f;
}

inline bool CircleToCircle(D3DXVECTOR2* _pCenter1, float _fRadius1, D3DXVECTOR2* _pCenter2, float _fRadius2)
{
	float fDist = (_pCenter1->x - _pCenter2->x) * (_pCenter1->x - _pCenter2->x) + (_pCenter1->y - _pCenter2->y) * (_pCenter1->y - _pCenter2->y);
	if(fDist > (_fRadius1 + _fRadius2) * (_fRadius1 + _fRadius2))
		return false;

	return true;
}

inline bool PointToCircle(D3DXVECTOR2* _pPoint, D3DXVECTOR2* _pCenter, float _fRadius)
{
	float fDist = (_pPoint->x - _pCenter->x) * (_pPoint->x - _pCenter->x) + (_pPoint->y - _pCenter->y) * (_pPoint->y - _pCenter->y);
	if(fDist > _fRadius * _fRadius)
		return false;

	return true;
}

inline bool PointToAABB(D3DXVECTOR2* _pPoint, D3DXVECTOR2* _pRectLB, D3DXVECTOR2* _pRectRT)
{
	if(_pRectLB->x <= _pPoint->x && _pPoint->x <= _pRectRT->x && _pRectLB->y <= _pPoint->y && _pPoint->y <= _pRectRT->y)
		return true;

	return false;
}

// http://dolphin.ivyro.net/file/mathematics/tutorial07.html
inline bool CircleToAABB(D3DXVECTOR2* _pCenter, float _fRadius, D3DXVECTOR2* _pRectLB, D3DXVECTOR2* _pRectRT)
{
	int iZoneX = ( _pCenter->x <  _pRectLB->x ) ? 0 : ( _pCenter->x > _pRectRT->x ) ? 2 : 1;
	int iZoneY = ( _pCenter->y <  _pRectLB->y ) ? 0 : ( _pCenter->y > _pRectRT->y ) ? 2 : 1;
	int iZone = iZoneX + 3 * iZoneY;

	// 1¹ø
	if(iZone == 4)
		return true;

	// 2¹ø
	if(iZone == 0 || iZone == 2 || iZone == 6 || iZone == 8)
	{
		D3DXVECTOR2 vCenter = ((*_pRectLB) + (*_pRectRT)) / 2.0f;
		D3DXVECTOR2 vCorner;

		vCorner.x = ( iZone == 0 || iZone == 6 ) ? vCenter.x - (_pRectRT->x - _pRectLB->x) / 2.0f : vCenter.x + (_pRectRT->x - _pRectLB->x) / 2.0f;
		vCorner.y = ( iZone == 0 || iZone == 2 ) ? vCenter.y - (_pRectRT->y - _pRectLB->y) / 2.0f : vCenter.y + (_pRectRT->y - _pRectLB->y) / 2.0f;

		if(PointToCircle(&vCorner, _pCenter, _fRadius))
			return true;
	}

	// 3¹ø
	if(iZone == 1 || iZone == 7)
	{
		if( fabs( _pCenter->y - (_pRectLB->y + _pRectRT->y) / 2.0f ) <= ( _fRadius + (_pRectRT->y - _pRectLB->y) / 2.0f ) )
			return true;
	}
	if(iZone == 3 || iZone == 5)
	{
		if( fabs( _pCenter->x - (_pRectLB->x + _pRectRT->x) / 2.0f ) <= ( _fRadius + (_pRectRT->x - _pRectLB->x) / 2.0f ) )
			return true;
	}

	return false;
}

inline bool AABBToAABB(D3DXVECTOR2* _pRectLB1, D3DXVECTOR2* _pRectRT1, D3DXVECTOR2* _pRectLB2, D3DXVECTOR2* _pRectRT2)
{
	if(_pRectLB1->x < _pRectRT2->x && _pRectRT1->x > _pRectLB2->x && _pRectRT1->y > _pRectLB2->y && _pRectLB1->y < _pRectRT2->y)
		return true;

	return false;
}

inline bool PointToOBB()
{
	return false;
}

inline bool CircleToOBB()
{
	return true;
}

inline bool OBBToOBB()
{
	return true;
}

inline bool PointInSphere(D3DXVECTOR3* _pPoint, D3DXVECTOR3* _pCenter, float _fRadius)
{
	float fDist = (_pPoint->x - _pCenter->x) * (_pPoint->x - _pCenter->x) + (_pPoint->y - _pCenter->y) * (_pPoint->y - _pCenter->y) + (_pPoint->z - _pCenter->z) * (_pPoint->z - _pCenter->z);
	if(fDist > _fRadius * _fRadius)
		return false;

	return true;
}