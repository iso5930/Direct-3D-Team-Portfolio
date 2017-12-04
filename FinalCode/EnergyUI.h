#pragma once

#include "UI.h"

class CEnergyUI : public CUI
{
protected:
	// Cur
	int m_iCur;

	// Max
	int m_iMax;

	// VertexArr
	Vertex m_VertexArr[4];

	// Frame
	Frame m_Frame;

	// Texture
	vector<LPDIRECT3DTEXTURE9> m_TextureVec;

	// BufferCom
	CBufferCom* m_pBufferCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CEnergyUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CEnergyUI();
};
