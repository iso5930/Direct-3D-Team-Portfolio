#pragma once

#include "Component.h"

class CTransformCom : public CComponent
{
public:
	// Axis
	D3DXVECTOR3 m_vAxisX;
	D3DXVECTOR3 m_vAxisY;
	D3DXVECTOR3 m_vAxisZ;

	// Pos, Angle, Size
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vAngle;
	D3DXVECTOR3 m_vSize;

	// Matrix
	D3DXMATRIX m_mTrans;
	D3DXMATRIX m_mRotate;
	D3DXMATRIX m_mScale;
	D3DXMATRIX m_mWorld;
	D3DXMATRIX m_mPreWorld;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CTransformCom();
	virtual ~CTransformCom();
};